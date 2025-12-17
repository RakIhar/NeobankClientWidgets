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

            QList<TransactionInfo> txs;
            txs.reserve(txArray.size());
            for (const auto &item : txArray)
                if (item.isObject())
                {
                    const auto txObj = item.toObject();
                    TransactionInfo info;
                    info.id             = txObj.value(toStr(JsonField::TransactionId)).toString();
                    info.accountId      = txObj.value(toStr(JsonField::AccountId)).toString();
                    info.amount         = txObj.value(toStr(JsonField::Amount)).toString();
                    info.currency       = txObj.value(toStr(JsonField::Currency)).toString();
                    info.type           = txObj.value(toStr(JsonField::Type)).toString();
                    info.description    = txObj.value(toStr(JsonField::Reason)).toString();
                    info.status         = txObj.value(toStr(JsonField::Status)).toString();
                    info.createdAt      = txObj.value(toStr(JsonField::CreatedAt)).toString();
                    txs.append(info);
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
            TransactionInfo info;
            const QJsonObject txObj = obj.value(toStr(JsonField::TrObj)).toObject();
            info.id          = txObj.value(toStr(JsonField::TransactionId)).toString();
            info.accountId   = txObj.value(toStr(JsonField::AccountId)).toString();
            info.amount      = txObj.value(toStr(JsonField::Amount)).toString();
            info.currency    = txObj.value(toStr(JsonField::Currency)).toString();
            info.type        = txObj.value(toStr(JsonField::Type)).toString();
            info.description = txObj.value(toStr(JsonField::Reason)).toString();
            info.status      = txObj.value(toStr(JsonField::Status)).toString();
            info.createdAt   = txObj.value(toStr(JsonField::CreatedAt)).toString();

            emit transactionCreated(info);
        }
        else
            emit transactionsFailed(reason);
    }
}

