#include "accountsservice.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "../constants.h"
#include "../deserializers.h"



void AccountsService::accountsListRequest(const int limit, const int page)
{
    QJsonObject request;
    authenticate(request);
    request[toStr(JsonField::Type)]  = toStr(ProtocolType::AccList);
    request[toStr(JsonField::Limit)] = limit;
    request[toStr(JsonField::Page)]  = page;

    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
}

void AccountsService::allAccountsListRequest()
{
    QJsonObject request;
    authenticate(request);
    request[toStr(JsonField::Type)]  = toStr(ProtocolType::AccList);
    request[toStr(JsonField::Limit)] = -1;

    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
}

void AccountsService::accountCreateRequest(const Enums::Currency currency)
{
    QJsonObject request;
    authenticate(request);
    request[toStr(JsonField::Type)]     = toStr(ProtocolType::AccCreate);
    request[toStr(JsonField::Currency)] = Enums::toStr(currency);

    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
}

void AccountsService::accountDeleteRequest(const Models::Account &account)
{
    QJsonObject request;
    authenticate(request);
    request[toStr(JsonField::Type)]      = toStr(ProtocolType::AccDelete);
    request[toStr(JsonField::AccountId)] = account.id;

    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
}

void AccountsService::handleMessage(const QByteArray &msg)
{
    QJsonObject obj      = QJsonDocument::fromJson(msg).object();
    const QString type   = obj.value(toStr(JsonField::Type)).toString();
    const bool result    = obj.value(toStr(JsonField::Result)).toBool();
    const QString reason = obj.value(toStr(JsonField::Error)).toString();

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
            emit accountsList(accounts);

            int total = obj.value(toStr(JsonField::Count)).toInt(0);
            int page  = obj.value(toStr(JsonField::Page)).toInt(0);
            int limit = obj.value(toStr(JsonField::Limit)).toInt(50);
            emit accountsCount(total, page, limit);
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
    else if (type == toStr(ProtocolType::AccDelete))
    {
        if (result)
            emit accountDeleted();
        else
            emit accountsFailed(reason);
    }
}
