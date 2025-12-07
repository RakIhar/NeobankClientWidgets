#include "authservice.h"
#include "../protocols/protocolvalidator.h"
#include "../pages/registrationpage.h"

AuthService::AuthService(QObject *parent)
    : QObject{parent}
{}

void AuthService::handleMessage(const QByteArray &msg)
{
    QJsonDocument doc;
    if (!ProtocolValidator::validateMessage(msg, doc))
        return;

    QJsonObject obj = doc.object();
    const QString type = obj.value("type").toString();
    const bool result = obj.value("result").toBool();
    const QString reason = obj.value("reason").toString();

    if (type == "login")
    {
        if (result)
            emit loginSuccess();
        else
            emit loginFailed(reason);
    }
    else if (type == "register")
    {
        if (result)
            emit registerSuccess();
        else
            emit registerFailed(reason);
    }
}


QByteArray AuthService::createLoginRequest(const QString &username, const QString &password)
{
    QJsonObject request;
    request["type"] = "login";
    // request["id"] = QString::number(QDateTime::currentMSecsSinceEpoch());
    request["username"] = username;
    request["password"] = password;
    QJsonDocument doc(request);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray AuthService::createRegistrationRequest(const RegData &regData)
{
    QJsonObject payload;
    payload["username"] = regData.username;
    payload["password"] = regData.password;
    payload["email"] = regData.email;
    payload["phone"] = regData.phone;

    QJsonObject request;
    request["type"] = "register";
    // request["id"] = QString::number(QDateTime::currentMSecsSinceEpoch());
    request["payload"] = payload;
    QJsonDocument doc(request);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    return data;
}

