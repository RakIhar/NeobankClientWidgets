#include "authservice.h"
#include "../pages/registrationpage.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "../constants.h"

AuthService::AuthService(QObject *parent)
    : QObject{parent}
{}

void AuthService::handleMessage(const QByteArray &msg)
{
    QJsonObject obj      = QJsonDocument::fromJson(msg).object();
    const QString type   = obj.value(toStr(JsonField::Type)).toString();
    const bool result    = obj.value(toStr(JsonField::Result)).toBool();
    const QString reason = obj.value(toStr(JsonField::Reason)).toString();

    if (type == toStr(ProtocolType::Login))
    {
        if (result)
        {
            this->session_id = obj.value(toStr(JsonField::SessionId)).toString();
            this->token      = obj.value(toStr(JsonField::Token)).toString();
            emit loginSuccess();
        }
        else
            emit loginFailed(reason);
    }
    else if (type == toStr(ProtocolType::Register))
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
    request[toStr(JsonField::Type)]     = toStr(ProtocolType::Login);
    request[toStr(JsonField::Username)] = username;
    request[toStr(JsonField::Password)] = password;
    QJsonDocument doc(request);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    return data;
}

QByteArray AuthService::createRegistrationRequest(const RegData &regData)
{
    QJsonObject request;
    request[toStr(JsonField::Type)]     = toStr(ProtocolType::Register);
    request[toStr(JsonField::Username)] = regData.username;
    request[toStr(JsonField::Password)] = regData.password;
    request[toStr(JsonField::Email)]    = regData.email;
    request[toStr(JsonField::Phone)]    = regData.phone;
    QJsonDocument doc(request);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    return data;
}

