#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <QObject>
#include <QJsonObject>
#include "../constants.h"

class RegData;
class AuthService : public QObject
{
    Q_OBJECT
public:
    explicit AuthService(QObject *parent = nullptr);
    void handleMessage(const QByteArray &msg);
    void setAuthentificationData(QJsonObject &request)
    {
        request[toStr(JsonField::SessionId)] = session_id;
        request[toStr(JsonField::Token)]     = token;
    }
    std::pair<QString, QString> getSessionData() const { return { session_id, token}; };
    QByteArray createLoginRequest(const QString &username, const QString &password);
    QByteArray createRegistrationRequest(const RegData &regData);
signals:
    void loginSuccess();
    void loginFailed(const QString &reason);
    void registerSuccess();
    void registerFailed(const QString &reason);
private:
    QString session_id;
    QString token;
};

#endif // AUTHSERVICE_H
