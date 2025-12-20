#include "transactionsservice.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "../deserializers.h"

void TransactionsService::createTrListRequest(const int limit , const int page)
{
    QJsonObject request;
    authenticate(request);
    request[toStr(JsonField::Type)]  = toStr(ProtocolType::TrList);
    request[toStr(JsonField::Limit)] = limit;
    request[toStr(JsonField::Page)]  = page;

    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
}

void TransactionsService::createTransferRequest(const TransferData &trData)
{
    QJsonObject request;
    authenticate(request);
    request[toStr(JsonField::Type)]    = toStr(ProtocolType::TrCreate);
    if (trData.from_acc.iban.has_value())
    request[toStr(JsonField::FromAcc)] = trData.from_acc.iban.value();
    else
    request[toStr(JsonField::FromAcc)] = trData.from_acc.id;
    if (trData.to_acc.iban.has_value())
    request[toStr(JsonField::ToAcc)]   = trData.to_acc.iban.value();
    else
    request[toStr(JsonField::ToAcc)]   = trData.to_acc.id;
    request[toStr(JsonField::Amount)]  = trData.from_amount;
    request[toStr(JsonField::Reason)]  = trData.description.has_value()
                                        ? QJsonValue(trData.description.value())
                                        : QJsonValue::Null;
    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
}

void TransactionsService::createCreditRequest(const CreditData &crData)
{
    QJsonObject request;
    authenticate(request);
    request[toStr(JsonField::Type)]      = toStr(ProtocolType::TrCreate);
    request[toStr(JsonField::AccountId)] = crData.acc.id;
    request[toStr(JsonField::Amount)]    = crData.amount;
    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
}

void TransactionsService::createBeforeTrRequest(const QString &to)
{
    QJsonObject request;
    authenticate(request);
    request[toStr(JsonField::Type)]  = toStr(ProtocolType::TrBefore);
    request[toStr(JsonField::ToAcc)] = to;
    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
}

void TransactionsService::handleMessage(const QByteArray &msg)
{
    QJsonObject obj      = QJsonDocument::fromJson(msg).object();
    const QString type   = obj.value(toStr(JsonField::Type)).toString();
    const bool result    = obj.value(toStr(JsonField::Result)).toBool();
    const QString reason = obj.value(toStr(JsonField::Reason)).toString();

    if (type == toStr(ProtocolType::TrList)) {
        if (result)
        {
            const QJsonArray txArray = obj.value(toStr(JsonField::TrArr)).toArray();

            QList<Models::Transaction> txs;
            txs.reserve(txArray.size());
            for (const auto &item : txArray)
                if (item.isObject())
                {
                    txs.append(deserializeTransaction(item.toObject()));
                }
            emit transactionsUpdated(txs);
        }
        else
            emit transactionsFailed(reason);
    }
    else if (type == toStr(ProtocolType::TrCreate))
    {
        if (result)
        {
            const QJsonObject txObj = obj.value(toStr(JsonField::TrObj)).toObject();
            Models::Transaction info = deserializeTransaction(txObj);
            emit transactionCreated(info);
        }
        else
            emit transactionsFailed(reason);
    }
}

TransactionsService::TransactionsService(SendDelegate send, AuthDelegate authenticate, QObject *parent)
    : QObject{parent}, send(send), authenticate(authenticate) {}
