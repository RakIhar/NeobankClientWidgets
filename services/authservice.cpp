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
    if (!obj.contains("type") || !(obj["type"].toString() == "auth"))
        return;

    if (obj.contains("subtype") && obj["subtype"].toString() == "login")
    {
        if (obj.contains("result") && obj["result"].toBool())
        {
            emit loginSuccess();
        }
        else if (obj.contains("result") && !obj["result"].toBool())
        {
            emit loginFailed(obj.contains("reason") ? obj["reason"].toString() : "");
        }
    }
    else if (obj.contains("subtype") && obj["subtype"].toString() == "register")
    {
        if (obj.contains("result") && obj["result"].toBool())
        {
            emit registerSuccess();
        }
        else if (obj.contains("result") && !obj["result"].toBool())
        {
            emit registerFailed(obj.contains("reason") ? obj["reason"].toString() : "");
        }
    }
}

QByteArray AuthService::createLoginRequest(const QString &username, const QString &password)
{
    QJsonObject payload;
    payload["username"] = username;
    payload["password"] = password;

    QJsonObject request;
    request["type"] = "auth";
    request["subtype"] = "login";
    // request["id"] = QString::number(QDateTime::currentMSecsSinceEpoch());
    request["payload"] = payload;
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
    request["type"] = "auth";
    request["subtype"] = "register";
    // request["id"] = QString::number(QDateTime::currentMSecsSinceEpoch());
    request["payload"] = payload;
    QJsonDocument doc(request);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    return data;
}

