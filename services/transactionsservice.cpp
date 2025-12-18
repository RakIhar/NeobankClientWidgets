#include "transactionsservice.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

TransactionsService::TransactionsService(QObject *parent)
    : QObject{parent}
{}

QByteArray TransactionsService::createTrListRequest(AuthDelegate authenticate, int limit)
{
    QJsonObject request;
    request[toStr(JsonField::Type)] = toStr(ProtocolType::TrList);
    authenticate(request);
    QJsonDocument doc(request);
    request[toStr(JsonField::Limit)] = limit;
    return doc.toJson(QJsonDocument::Compact);
}

QByteArray TransactionsService::createTransferRequest(AuthDelegate authenticate, const QString &fromAccount, const QString &to, const QString &amount, const Enums::Currency &curr, const QString &description)
{
    QJsonObject request;
    request[toStr(JsonField::Type)]     = toStr(ProtocolType::TrCreate);
    authenticate(request);
    request[toStr(JsonField::FromAcc)]  = fromAccount;
    request[toStr(JsonField::ToAcc)]    = to;
    request[toStr(JsonField::Amount)]   = amount;
    request[toStr(JsonField::Currency)] = Enums::toStr(curr);
    request[toStr(JsonField::Reason)]   = description;

    QJsonDocument doc(request);
    return doc.toJson(QJsonDocument::Compact);
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

Models::Transaction TransactionsService::deserializeTransaction(const QJsonObject &txObj)
{
    Models::Transaction info;
    info.id         = txObj.value(toStr(JsonField::TransactionId)).toVariant().toLongLong();
    info.account_id = txObj.value(toStr(JsonField::AccountId)).toVariant().toLongLong();

    QJsonValue cpVal = txObj.value(toStr(JsonField::CounterpartyId));
    if (!cpVal.isNull()) {
        info.counterparty_account_id = cpVal.toVariant().toLongLong(); //для безопасности
    }

    info.amount   = txObj.value(toStr(JsonField::Amount)).toString();
    info.currency = txObj.value(toStr(JsonField::Currency)).toString();
    info.type     = txObj.value(toStr(JsonField::Type)).toString();

    QJsonValue descVal = txObj.value(toStr(JsonField::Reason));
    if (!descVal.isNull()) info.description = descVal.toString();

    QJsonValue statusVal = txObj.value(toStr(JsonField::Status));
    if (!statusVal.isNull()) info.status = statusVal.toString();

    QJsonValue dateVal = txObj.value(toStr(JsonField::CreatedAt));
    if (!dateVal.isNull()) {
        info.created_at = QDateTime::fromString(dateVal.toString(), Qt::ISODate);
    }

    return info;
}

