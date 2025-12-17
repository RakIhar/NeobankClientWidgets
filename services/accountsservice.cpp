#include "accountsservice.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "../constants.h"

AccountsService::AccountsService(QObject *parent)
    : QObject{parent}
{}

QByteArray AccountsService::createAccListRequest(AuthDelegate authenticate)
{
    QJsonObject request;
    request[toStr(JsonField::Type)] = toStr(ProtocolType::AccList);
    authenticate(request);
    QJsonDocument doc(request);
    return doc.toJson(QJsonDocument::Compact);
}

QByteArray AccountsService::createAccCreateRequest(AuthDelegate authenticate, const QString &currency)
{
    QJsonObject request;
    request[toStr(JsonField::Type)] = toStr(ProtocolType::AccCreate);
    authenticate(request);
    if (!currency.isEmpty())
        request[toStr(JsonField::Currency)] = currency;
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

            QList<AccountInfo> accounts;
            accounts.reserve(accountsArray.size());
            for (const auto &item : accountsArray)
                if (item.isObject())
                {
                    const QJsonObject accObj = item.toObject();
                    AccountInfo info;
                    info.id       = accObj.value(toStr(JsonField::AccountId)).toVariant().toString();
                    info.iban     = accObj.value(toStr(JsonField::Iban)).toString();
                    info.balance  = accObj.value(toStr(JsonField::Balance)).toVariant().toString();
                    info.currency = accObj.value(toStr(JsonField::Currency)).toString();
                    info.status   = accObj.value(toStr(JsonField::Status)).toString();
                    accounts.append(info);
                }
            emit accountsUpdated(accounts);
        }
        else
            emit accountsFailed(reason);
    }
    else if (type == toStr(ProtocolType::AccCreate))
    {
        if (result)
        {
            const QJsonObject accObj = obj.value(toStr(JsonField::AccObj)).toObject();
            AccountInfo info;
            info.id       = accObj.value(toStr(JsonField::AccountId)).toVariant().toString();
            info.iban     = accObj.value(toStr(JsonField::Iban)).toString();
            info.balance  = accObj.value(toStr(JsonField::Balance)).toVariant().toString();
            info.currency = accObj.value(toStr(JsonField::Currency)).toString();
            info.status   = accObj.value(toStr(JsonField::Status)).toString();

            emit accountCreated(info);
        }
        else
            emit accountsFailed(reason);
    }
}
