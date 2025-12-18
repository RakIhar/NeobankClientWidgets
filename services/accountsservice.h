#ifndef ACCOUNTSSERVICE_H
#define ACCOUNTSSERVICE_H
#include <QObject>
#include <QDateTime>
#include "../constants.h"

struct AccountInfo
{
    QString id;
    QString iban;
    QString balance;
    QString currency;
    QString status;
};

namespace Models {

struct Account
{
    qint64 id = 0;
    qint64 user_id = 0;
    QString iban;
    QString balance = "0.00";
    QString currency;
    QString status = QStringLiteral("active");
    QDateTime created_at;
    QDateTime updated_at;
};

}

class AccountsService : public QObject
{
    Q_OBJECT
public:
    explicit AccountsService(QObject *parent = nullptr);
    QByteArray createAccListRequest(AuthDelegate authenticate);
    QByteArray createAccCreateRequest(AuthDelegate authenticate, const QString &currency = QString());
    void handleMessage(const QByteArray &msg);

signals:
    void accountsUpdated(const QList<AccountInfo> &accounts);
    void accountsFailed(const QString &reason);
    void accountCreated(const AccountInfo &account);
};

#endif // ACCOUNTSSERVICE_H
