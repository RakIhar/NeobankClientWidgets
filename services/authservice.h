#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <QObject>

class RegData;
class AuthService : public QObject
{
    Q_OBJECT
public:
    explicit AuthService(QObject *parent = nullptr);
    void handleMessage(const QByteArray &msg);
    QByteArray createLoginRequest(const QString &username, const QString &password);
    QByteArray createRegistrationRequest(const RegData &regData);
signals:
    void loginSuccess();
    void loginFailed(const QString &reason);
    void registerSuccess();
    void registerFailed(const QString &reason);
};

#endif // AUTHSERVICE_H
