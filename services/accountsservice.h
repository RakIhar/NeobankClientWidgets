#ifndef ACCOUNTSSERVICE_H
#define ACCOUNTSSERVICE_H
#include <QObject>
#include <QDateTime>
#include "../constants.h"
#include "../models/account.h"

class AccountsService : public QObject
{
    Q_OBJECT
public:
    explicit AccountsService(SendDelegate send, AuthDelegate authenticate, QObject *parent = nullptr);
    void createAccListRequest(const int limit = 50, const int page = 0);
    void createAccCreateRequest(const Enums::Currency currency);
    void handleMessage(const QByteArray &msg);

signals:
    void accountsUpdated(const QList<Models::Account> &accounts);
    void accountsFailed(const QString &reason);
    void accountCreated(const Models::Account &account);

private:
    SendDelegate send;
    AuthDelegate authenticate;
};

#endif // ACCOUNTSSERVICE_H
