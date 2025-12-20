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
    explicit TransactionsService(SendDelegate send, AuthDelegate authenticate, QObject *parent);
    void createTrListRequest(const int limit = 50, const int page = 0);
    void createTransferRequest(const TransferData& trData);
    void createCreditRequest(const CreditData& crData);
    void createBeforeTrRequest(const QString& to);
    void handleMessage(const QByteArray &msg);

signals:
    void transactionsUpdated(const QList<Models::Transaction> &transactions);
    void transactionsFailed(const QString &reason);
    void transactionCreated(const Models::Transaction &transaction);
    void beforeTransferInfo(const BeforeTransferInfo& info);

private:
    SendDelegate send;
    AuthDelegate authenticate;
};

#endif // TRANSACTIONSSERVICE_H

