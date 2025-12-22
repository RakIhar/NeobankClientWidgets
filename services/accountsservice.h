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
    explicit AccountsService(SendDelegate send, AuthDelegate authenticate, QObject *parent = nullptr)
        : QObject{parent}, send(send), authenticate(authenticate) {}
    void accountsListRequest(const int limit = 50, const int page = 0);
    void allAccountsListRequest();
    void accountCreateRequest(const Enums::Currency currency);
    void accountDeleteRequest(const Models::Account &account);
    void handleMessage(const QByteArray &msg);

signals:
    void accountsList(const QList<Models::Account> &accounts);
    void accountsFailed(const QString &reason);
    void accountCreated(const Models::Account &account);
    void accountDeleted();
    void accountsCount(int total, int page, int limit);

private:
    SendDelegate send;
    AuthDelegate authenticate;
};

#endif // ACCOUNTSSERVICE_H
