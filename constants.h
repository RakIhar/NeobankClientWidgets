#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>
#include <QJsonObject>
#include <QMetaEnum>
using AuthDelegate = std::function<void(QJsonObject&)>;

enum class ProtocolType
{
    Login,
    Register,
    Authorization,
    AccList,
    TrList,
    AccCreate,
    TrCreate
};

inline QString toStr(ProtocolType type)
{
    switch(type) {
    case ProtocolType::Login:         return "login";
    case ProtocolType::Register:      return "register";
    case ProtocolType::Authorization: return "authorization";
    case ProtocolType::AccList:       return "account.list";
    case ProtocolType::TrList:        return "transaction.list";
    case ProtocolType::AccCreate:     return "account.create";
    case ProtocolType::TrCreate:      return "transaction.create";
    }
    return {};
}

enum class JsonField
{
    UserId,
    AccountId,
    Iban,
    Balance,
    Currency,
    Status,
    CreatedAt,
    UpdatedAt,
    CounterpartyId,
    FromAcc,
    ToAcc,

    Username,
    Password,
    PasswordHash,
    Email,

    TransactionId,
    Amount,
    Type,
    Subtype,
    Timestamp,
    SessionId,
    Token,
    Result,
    Reason,
    ReasonCode,
    Phone,
    Metadata,

    AccObj,
    AccArr,
    TrObj,
    TrArr,

    Limit,
    Page
};

inline QString toStr(JsonField field)
{
    switch(field)
    {
    case JsonField::UserId:         return "user_id";
    case JsonField::Username:       return "username";
    case JsonField::Password:       return "password";
    case JsonField::PasswordHash:   return "password_hash";
    case JsonField::Email:          return "email";
    case JsonField::AccountId:      return "account_id";
    case JsonField::Balance:        return "balance";
    case JsonField::Currency:       return "currency";
    case JsonField::TransactionId:  return "transaction_id";
    case JsonField::Amount:         return "amount";
    case JsonField::Type:           return "type";
    case JsonField::Subtype:        return "subtype";
    case JsonField::Timestamp:      return "timestamp";
    case JsonField::SessionId:      return "session_id";
    case JsonField::Token:          return "token";
    case JsonField::Result:         return "result";
    case JsonField::Reason:         return "reason";
    case JsonField::ReasonCode:     return "reason_code";
    case JsonField::Phone:          return "phone";
    case JsonField::Iban:           return "iban";
    case JsonField::Status:         return "status";
    case JsonField::CreatedAt:      return "created_at";
    case JsonField::UpdatedAt:      return "updated_at";
    case JsonField::AccObj:         return "account";
    case JsonField::AccArr:         return "accounts";
    case JsonField::TrObj:          return "transaction";
    case JsonField::TrArr:          return "transactions";
    case JsonField::CounterpartyId: return "counterparty_account_id";
    case JsonField::Limit:          return "limit";
    case JsonField::Page:           return "page";
    case JsonField::FromAcc:        return "from";
    case JsonField::ToAcc:          return "to";
    case JsonField::Metadata:       return "metadata";
    }
    return {};
}

class Enums : public QObject
{
    Q_OBJECT
public:
    enum class Currency
    {
        BYN,
        RUB,
        USD,
        EUR,
        GBP,
        KZT,
        UAH,
        PLN,
        CNY
    };
    Q_ENUM(Currency)

    static inline QString toSymbol(Currency currency)
    {
        switch(currency) {
        case Currency::BYN: return "Br";
        case Currency::RUB: return "₽";
        case Currency::USD: return "$";
        case Currency::EUR: return "€";
        case Currency::GBP: return "£";
        case Currency::CNY: return "¥";
        case Currency::KZT: return "₸";
        default:            return "";
        }
    }
    static QString toStr(Currency currency)
    {
        const int value = static_cast<int>(currency);
        const char* key = QMetaEnum::fromType<Currency>().valueToKey(value);
        return key ? QString::fromLatin1(key) : QString();
    }
    static Currency fromStr(const QString &str, Currency defaultValue = Currency::BYN) {
        bool isCorrect;
        int value = QMetaEnum::fromType<Currency>().keyToValue(str.toUpper().toLatin1().data(), &isCorrect);
        return isCorrect ? static_cast<Currency>(value) : defaultValue;
    }
};
Q_DECLARE_METATYPE(Enums::Currency)
#endif // CONSTANTS_H
