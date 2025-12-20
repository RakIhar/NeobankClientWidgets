#ifndef DESERIALIZERS_H
#define DESERIALIZERS_H
#include "QJsonObject"
#include "constants.h"
#include "models/transaction.h"
#include "models/account.h"

inline Models::Transaction deserializeTransaction(const QJsonObject &txObj)
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

inline Models::Account deserializeAccount(const QJsonObject &accObj)
{
    Models::Account acc;
    acc.id          = accObj.value(toStr(JsonField::AccountId)).toVariant().toLongLong();
    acc.user_id     = accObj.value(toStr(JsonField::UserId)).toVariant().toLongLong();
    acc.currency    = accObj.value(toStr(JsonField::Currency)).toString();

    QJsonValue ibanVal                    = accObj.value(toStr(JsonField::Iban));
    if (!ibanVal.isNull())    acc.iban    = ibanVal.toString();

    QJsonValue statusVal                  = accObj.value(toStr(JsonField::Status));
    if (!statusVal.isNull())  acc.status  = statusVal.toString();

    QJsonValue balanceVal                 = accObj.value(toStr(JsonField::Balance));
    if (!balanceVal.isNull()) acc.balance = balanceVal.toString();

    QJsonValue crAtVal = accObj.value(toStr(JsonField::CreatedAt));
    if (!crAtVal.isNull()) {
        acc.created_at = QDateTime::fromString(crAtVal.toString(), Qt::ISODate);
    }

    QJsonValue upAtVal = accObj.value(toStr(JsonField::UpdatedAt));
    if (!upAtVal.isNull()) {
        acc.updated_at = QDateTime::fromString(upAtVal.toString(), Qt::ISODate);
    }

    return acc;
}

#endif // DESERIALIZERS_H
