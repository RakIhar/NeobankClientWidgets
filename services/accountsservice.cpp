#include "accountsservice.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "../constants.h"
#include "../deserializers.h"

AccountsService::AccountsService(SendDelegate send, AuthDelegate authenticate, QObject *parent)
    : QObject{parent}, send(send), authenticate(authenticate) {}

void AccountsService::createAccListRequest(const int limit, const int page)
{
    QJsonObject request;
    authenticate(request);
    request[toStr(JsonField::Type)]  = toStr(ProtocolType::AccList);
    request[toStr(JsonField::Limit)] = limit;
    request[toStr(JsonField::Page)]  = page;

    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
}

void AccountsService::createAccCreateRequest(const Enums::Currency currency)
{
    QJsonObject request;
    authenticate(request);
    request[toStr(JsonField::Type)]     = toStr(ProtocolType::AccCreate);
    request[toStr(JsonField::Currency)] = Enums::toStr(currency);

    QJsonDocument doc(request);
    send(doc.toJson(QJsonDocument::Compact));
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
