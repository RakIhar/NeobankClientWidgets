#ifndef DESERIALIZERS_H
#define DESERIALIZERS_H
#include "QJsonObject"
#include "constants.h"
#include "models/transaction.h"
#include "models/account.h"

//std::optional - поле может отсутствовать вовсе

inline Models::Transaction deserializeTransaction(const QJsonObject &txObj)
{
    Models::Transaction info;
    info.id         = txObj.value(toStr(JsonField::TransactionId)).toVariant().toLongLong();
    info.account_id = txObj.value(toStr(JsonField::AccountId)).toVariant().toLongLong();

    if (txObj.contains(toStr(JsonField::CounterpartyId)))
        info.counterparty_account_id = txObj.value(toStr(JsonField::CounterpartyId)).toVariant().toLongLong();

    info.amount   = txObj.value(toStr(JsonField::Amount)).toString();
    info.currency = txObj.value(toStr(JsonField::Currency)).toString();
    info.type     = txObj.value(toStr(JsonField::Type)).toString();

    if (txObj.contains(toStr(JsonField::Descr)))
        info.description = txObj.value(toStr(JsonField::Descr)).toString();

    if (txObj.contains(toStr(JsonField::Status)))
        info.status = txObj.value(toStr(JsonField::Status)).toString();

    if (txObj.contains(toStr(JsonField::Metadata)))
        info.metadata = txObj.value(toStr(JsonField::Metadata)).toObject();

    if (txObj.contains(toStr(JsonField::CreatedAt)))
    {
        QString dateStr = txObj.value(toStr(JsonField::CreatedAt)).toString();
        info.created_at = QDateTime::fromString(dateStr, Qt::ISODate);
    }

    return info;
}

inline Models::Account deserializeAccount(const QJsonObject &accObj)
{
    Models::Account acc;
    acc.id          = accObj.value(toStr(JsonField::AccountId)).toVariant().toLongLong();
    acc.user_id     = accObj.value(toStr(JsonField::UserId)).toVariant().toLongLong();
    acc.currency    = accObj.value(toStr(JsonField::Currency)).toString();

    if (accObj.contains(toStr(JsonField::Iban)))
        acc.iban = accObj.value(toStr(JsonField::Iban)).toString();

    if (accObj.contains(toStr(JsonField::Balance)))
        acc.balance = accObj.value(toStr(JsonField::Balance)).toString();

    if (accObj.contains(toStr(JsonField::Status)))
        acc.status = accObj.value(toStr(JsonField::Status)).toString();

    if (accObj.contains(toStr(JsonField::CreatedAt)))
    {
        QString dateStr = accObj.value(toStr(JsonField::CreatedAt)).toString();
        acc.created_at  = QDateTime::fromString(dateStr, Qt::ISODate);
    }

    if (accObj.contains(toStr(JsonField::UpdatedAt)))
    {
        QString dateStr = accObj.value(toStr(JsonField::UpdatedAt)).toString();
        acc.updated_at  = QDateTime::fromString(dateStr, Qt::ISODate);
    }

    return acc;
}

inline BeforeTransferInfo deserializeBeforeTransferInfo(const QJsonObject &obj)
{
    BeforeTransferInfo info;

    info.isAllowed    = obj.value(toStr(JsonField::Result)).toBool();
    info.error        = obj.value(toStr(JsonField::Error)).toString();
    info.comission    = obj.value(toStr(JsonField::Comission)).toString();
    info.exchangeRate = obj.value(toStr(JsonField::ExchangeRate)).toString();
    info.resultAmount = obj.value(toStr(JsonField::Amount)).toString();

    if (obj.contains(toStr(JsonField::AccObj)))
        info.to_acc = deserializeAccount(obj.value(toStr(JsonField::AccObj)).toObject());

    return info;
}

#endif // DESERIALIZERS_H
