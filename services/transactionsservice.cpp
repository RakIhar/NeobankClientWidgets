#include "transactionsservice.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "../deserializers.h"

void TransactionsService::transactionsListRequest(const int limit , const int page)
{
    QJsonObject request;
    authenticate(request);

    request[toStr(JsonField::Type)]  = toStr(ProtocolType::TrList);
    request[toStr(JsonField::Limit)] = limit;
    request[toStr(JsonField::Page)]  = page;

    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
}

void TransactionsService::transferRequest(const TransferData &trData)
{
    QJsonObject request;
    authenticate(request);

    request[toStr(JsonField::Type)]    = toStr(ProtocolType::TrCreate);
    request[toStr(JsonField::FromAcc)] = trData.from_acc.id;
    request[toStr(JsonField::ToAcc)]   = trData.to_acc.id;
    request[toStr(JsonField::Amount)]  = trData.from_amount;
    request[toStr(JsonField::Descr)]   = trData.description;

    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
}

void TransactionsService::creditRequest(const CreditData &crData)
{
    QJsonObject request;
    authenticate(request);

    request[toStr(JsonField::Type)]      = toStr(ProtocolType::CreditCreate);
    request[toStr(JsonField::AccountId)] = crData.acc.id;
    request[toStr(JsonField::Amount)]    = crData.amount;

    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
}

void TransactionsService::beforeTransferInfoRequest(const QString &to, const QString &amount, const QString &from)
{
    QJsonObject request;
    authenticate(request);

    request[toStr(JsonField::Type)]  = toStr(ProtocolType::TrBefore);
    request[toStr(JsonField::ToAcc)] = to;
    request[toStr(JsonField::Amount)] = amount;
    request[toStr(JsonField::FromAcc)] = QJsonValue(from);

    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
}

void TransactionsService::handleMessage(const QByteArray &msg)
{
    QJsonObject obj      = QJsonDocument::fromJson(msg).object();
    const QString type   = obj.value(toStr(JsonField::Type)).toString();
    const bool result    = obj.value(toStr(JsonField::Result)).toBool();
    const QString reason = obj.value(toStr(JsonField::Error)).toString();

    if (type == toStr(ProtocolType::TrList)) {
        if (result)
        {
            const QJsonArray txArray = obj.value(toStr(JsonField::TrArr)).toArray();

            QList<Models::Transaction> txs;
            txs.reserve(txArray.size());
            for (const auto &item : txArray)
                if (item.isObject())
                    txs.append(deserializeTransaction(item.toObject()));
            emit transactionsList(txs);

            int total = obj.value(toStr(JsonField::Count)).toInt(0);
            int page  = obj.value(toStr(JsonField::Page)).toInt(0);
            int limit = obj.value(toStr(JsonField::Limit)).toInt(50);
            emit transactionsCount(total, page, limit);
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
    else if (type == toStr(ProtocolType::TrBefore))
        emit beforeTransferInfo(deserializeBeforeTransferInfo(obj.value(toStr(JsonField::TrObj)).toObject()));
}

/* TODO:
Received JSON:
 {
    "error": "Account is not available for credit",
    "result": false,
    "type": "credit.create"
}

Unknown message type "credit.create"
*/


