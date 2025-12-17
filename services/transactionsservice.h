#ifndef TRANSACTIONSSERVICE_H
#define TRANSACTIONSSERVICE_H

#include <QObject>
#include <QString>
#include <QList>
#include <QByteArray>
#include "../constants.h"

namespace Models {

struct Transaction
{
    qint64 id = 0;
    qint64 account_id = 0;
    qint64 counterparty_account_id = 0;
    QString amount = "0.00"; //оказывается с++ не имеет типа decimal
    QString currency;
    QString type;
    QString description;
    QString status = QStringLiteral("pending");
    QJsonObject metadata;
    QDateTime created_at;
};

}

struct TransactionInfo
{
    QString id;
    QString accountId;
    QString CounterpartyId;
    QString amount;
    QString currency;
    QString type;
    QString description;
    QString status;
    QString createdAt;
};

class TransactionsService : public QObject
{
    Q_OBJECT
public:
    explicit TransactionsService(QObject *parent = nullptr);
    QByteArray createTrListRequest(AuthDelegate authenticate, int limit = 50);
    QByteArray createTransferRequest(AuthDelegate authenticate,
                                     const QString &fromAccount, const QString &to,
                                     const QString &amount, const Enums::Currency &curr,
                                     const QString &description);
    QByteArray createTransferRequest(const QString &sessionId, const QString &token,
                                    const QString &fromAccount, const QString &to,
                                    const QString &amount, const QString &currency,
                                    const QString &description); //CHECK
    void handleMessage(const QByteArray &msg);

signals:
    void transactionsUpdated(const QList<TransactionInfo> &transactions);
    void transactionsFailed(const QString &reason);
    void transactionCreated(const TransactionInfo &transaction);
};

#endif // TRANSACTIONSSERVICE_H

