#ifndef TRANSACTIONSSERVICE_H
#define TRANSACTIONSSERVICE_H

#include <QObject>
#include <QString>
#include <QList>
#include <QByteArray>
#include "../constants.h"
#include "../models/transaction.h"

class TransactionsService : public QObject
{
    Q_OBJECT
    Models::Transaction deserializeTransaction(const QJsonObject &txObj);
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
                                    const QString &description);
    void handleMessage(const QByteArray &msg);

signals:
    void transactionsUpdated(const QList<Models::Transaction> &transactions);
    void transactionsFailed(const QString &reason);
    void transactionCreated(const Models::Transaction &transaction);
};

#endif // TRANSACTIONSSERVICE_H

