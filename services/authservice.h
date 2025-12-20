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
    explicit AuthService(SendDelegate send, QObject *parent = nullptr);
    void handleMessage(const QByteArray &msg);
    void setAuthentificationData(QJsonObject &request);
    std::pair<QString, QString> getSessionData() const { return { session_id, token}; };
    void createLoginRequest(const QString &username, const QString &password);
    void createRegistrationRequest(const RegData &regData);

signals:
    void loginSuccess();
    void loginFailed(const QString &reason);
    void registerSuccess();
    void registerFailed(const QString &reason);

private:
    QString session_id;
    QString token;
    SendDelegate send;
};

#endif // AUTHSERVICE_H
