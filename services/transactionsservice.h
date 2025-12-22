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

public:
    explicit TransactionsService(SendDelegate send, AuthDelegate authenticate, QObject *parent)
        : QObject{parent}, send(send), authenticate(authenticate) {}
    void transactionsListRequest(const int limit = 50, const int page = 0);
    void transferRequest(const TransferData& trData);
    void creditRequest(const CreditData& crData);
    void beforeTransferInfoRequest(const QString& to, const QString &amount = QString(), const QString &from = QString());
    void handleMessage(const QByteArray &msg);

signals:
    void transactionsList(const QList<Models::Transaction> &transactions);
    void transactionsFailed(const QString &reason);
    void transactionCreated(const Models::Transaction &transaction);
    void beforeTransferInfo(const BeforeTransferInfo& info);
    void transactionsCount(int total, int page, int limit);

private:
    SendDelegate send;
    AuthDelegate authenticate;
};

#endif // TRANSACTIONSSERVICE_H

