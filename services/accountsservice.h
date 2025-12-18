#ifndef ACCOUNTSSERVICE_H
#define ACCOUNTSSERVICE_H
#include <QObject>
#include <QDateTime>
#include "../constants.h"
#include "../models/account.h"

class AccountsService : public QObject
{
    Q_OBJECT
    Models::Account deserializeAccount(const QJsonObject &txObj);
public:
    explicit AccountsService(QObject *parent = nullptr);
    QByteArray createAccListRequest(AuthDelegate authenticate, const int limit = 50, const int page = 0);
    QByteArray createAccCreateRequest(AuthDelegate authenticate, const Enums::Currency currency);
    void handleMessage(const QByteArray &msg);

signals:
    void accountsUpdated(const QList<Models::Account> &accounts);
    void accountsFailed(const QString &reason);
    void accountCreated(const Models::Account &account);
};

#endif // ACCOUNTSSERVICE_H
