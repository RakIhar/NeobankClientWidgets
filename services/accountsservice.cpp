#include "accountsservice.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "../constants.h"

Models::Account AccountsService::deserializeAccount(const QJsonObject &accObj)
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

AccountsService::AccountsService(QObject *parent)
    : QObject{parent}
{}

QByteArray AccountsService::createAccListRequest(AuthDelegate authenticate, const int limit, const int page)
{
    QJsonObject request;
    authenticate(request);
    request[toStr(JsonField::Type)]  = toStr(ProtocolType::AccList);
    request[toStr(JsonField::Limit)] = limit;
    request[toStr(JsonField::Page)]  = page;

    QJsonDocument doc(request);
    return doc.toJson(QJsonDocument::Compact);
}

QByteArray AccountsService::createAccCreateRequest(AuthDelegate authenticate, const Enums::Currency currency)
{
    QJsonObject request;
    authenticate(request);
    request[toStr(JsonField::Type)]     = toStr(ProtocolType::AccCreate);
    request[toStr(JsonField::Currency)] = Enums::toStr(currency);

    QJsonDocument doc(request);
    return doc.toJson(QJsonDocument::Compact);
}

void AccountsService::handleMessage(const QByteArray &msg)
{
    QJsonObject obj      = QJsonDocument::fromJson(msg).object();
    const QString type   = obj.value(toStr(JsonField::Type)).toString();
    const bool result    = obj.value(toStr(JsonField::Result)).toBool();
    const QString reason = obj.value(toStr(JsonField::Reason)).toString();

    if (type == toStr(ProtocolType::AccList))
    {
        if (result)
        {
            const QJsonArray accountsArray = obj.value(toStr(JsonField::AccArr)).toArray();

            QList<Models::Account> accounts;
            accounts.reserve(accountsArray.size());
            for (const auto &item : accountsArray)
                if (item.isObject())
                    accounts.append(deserializeAccount(item.toObject()));
            emit accountsUpdated(accounts);
        }
        else
            emit accountsFailed(reason);
    }
    else if (type == toStr(ProtocolType::AccCreate))
    {
        if (result)
            emit accountCreated(deserializeAccount(obj.value(toStr(JsonField::AccObj)).toObject()));
        else
            emit accountsFailed(reason);
    }
}
