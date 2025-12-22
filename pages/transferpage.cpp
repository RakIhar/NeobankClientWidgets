#include "transferpage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDoubleValidator>
#include <QMessageBox>
#include "../converters.h"


TransferPage::TransferPage(TransactionsService *trService,
                           QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TransferDialog)
    , m_trService(trService)
{
    ui->setupUi(this);
    ui->amountEdit->setValidator(new QDoubleValidator(0.01, 1e12, 2, this));
    setupConnections();
}

TransferPage::~TransferPage() { delete ui; }

void TransferPage::setupConnections()
{
    connect(ui->sendButton, &QPushButton::clicked, this, [this]{
        std::pair<qint64, bool> amount = Money::toCents(ui->amountEdit->text(), false); //без знака

        if (amount.first && amount.second) {
            ui->sendButton->setEnabled(false);  //КНОПКИ: send off - обе ждут ответа от сервера
            ui->cancelButton->setEnabled(false);//КНОПКИ: cancel off

            ui->statusLabel->setText(tr("> Выполнение транзакции... <"));
            ui->statusLabel->setProperty("state", "loading");
            ui->statusLabel->style()->polish(ui->statusLabel);

            m_data.from_amount = Money::fromCents(amount.first); //приведение к корректной форме
            m_data.description = ui->descriptionEdit->text();

            m_trService->transferRequest(m_data);
        }
        else
            QMessageBox::warning(this, tr("Неверная сумма"), tr("Введите корректную положительную сумму"));
    });

    connect(ui->beforeTrInfoButton, &QPushButton::clicked, this,
    [this]{
        const QString to = ui->toEdit->text().trimmed();
        if (!to.isEmpty())
        {
            ui->statusLabel->setText(tr("> Ожидание информации... <"));
            ui->statusLabel->setProperty("state", "loading");
            ui->statusLabel->style()->polish(ui->statusLabel);
            ui->beforeTrInfoButton->setEnabled(false); //КНОПКИ: beforeTrInfoButton off - включится при изменении amount либо to
            ui->sendButton->setEnabled(false);         //КНОПКИ: включится на положительном ответе от сервера: усложнить протокол
            QString from   = QString::number(m_data.from_acc.id);
            QString amount = ui->amountEdit->text();
            m_trService->beforeTransferInfoRequest(to, amount, from);
        }
        else
            QMessageBox::warning(this, tr("Неверный получатель"), tr("Введите корректного получателя"));
    });

    connect(ui->cancelButton, &QPushButton::clicked, this,
    [this]{
        emit pr_back();
    });

    connect(ui->toEdit, &QLineEdit::textChanged, this,
    [this](const QString &text){
        ui->statusLabel->setText(tr(""));
        ui->statusLabel->setProperty("state", "");
        ui->statusLabel->style()->polish(ui->statusLabel);
        ui->sendButton->setEnabled(false); //КНОПКИ: send off - ждёт ответа от сервера

        std::pair<qint64, bool> amount  = Money::toCents(ui->amountEdit->text(), false);
        std::pair<qint64, bool> balance = Money::toCents(m_data.from_acc.balance.value_or("0.00"), false);
        bool isEnabled =    !text.trimmed().isEmpty() &&
                            amount.first &&
                            amount.second &&
                            balance.first &&
                            balance.second &&
                            balance.first >= amount.first;

        ui->beforeTrInfoButton->setEnabled(isEnabled);
        setInfoText();
    });

    connect(ui->amountEdit, &QLineEdit::textChanged, this,
    [this](const QString &text){
        ui->sendButton->setEnabled(false); //КНОПКИ: send off - ждёт ответа от сервера
        setInfoText();
        std::pair<qint64, bool> amount  = Money::toCents(text, false);
        std::pair<qint64, bool> balance = Money::toCents(m_data.from_acc.balance.value_or("0.00"), false);
        bool isEnabled =    amount.first &&
                            amount.second &&
                            balance.first &&
                            balance.second &&
                            balance.first >= amount.first;
        ui->beforeTrInfoButton->setEnabled(isEnabled);
    });

    connect(m_trService, &TransactionsService::beforeTransferInfo,
            this, &TransferPage::onBeforeTransferInfo);

    connect(m_trService, &TransactionsService::transactionsFailed, this,
    [this](const QString& rsn){
        ui->cancelButton->setEnabled(true);

        ui->statusLabel->setText(tr("> Ошибка транзакции: %1 <").arg(rsn));
        ui->statusLabel->setProperty("state", "error");
        ui->statusLabel->style()->polish(ui->statusLabel);

        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось выполнить перевод: %1").arg(rsn));
    });

    connect(m_trService, &TransactionsService::transactionCreated, this,
    [this](const Models::Transaction& tx){
        ui->statusLabel->setText(tr("> Транзакция успешно завершена <"));
        ui->statusLabel->setProperty("state", "success");
        ui->statusLabel->style()->polish(ui->statusLabel);

        QString details = tr(
            "ID транзакции: %1\n"
            "Сумма: %2 %3\n"
            "Тип: %4\n"
            "Дата: %5"
            ).arg(tx.id)
            .arg(tx.amount,
                tx.currency,
                tx.type,
                tx.created_at.has_value()
                   ? tx.created_at->toString("dd.MM.yyyy HH:mm")
                   : "-");

        if (tx.description.has_value())
            details += tr("\nОписание: %1").arg(tx.description.value());

        QMessageBox::information(this, tr("Успех"), tr("Перевод выполнен!\n\n%1").arg(details));
        emit pr_back();
    });
}

void TransferPage::reset(const Models::Account &from)
{
    m_data.from_acc = from;
    ui->toEdit->setText("");
    ui->amountEdit->setText("0.00");
    ui->descriptionEdit->setText("");

    ui->sendButton->setEnabled(false);
    ui->beforeTrInfoButton->setEnabled(false);
    ui->cancelButton->setEnabled(true);

    ui->statusLabel->setText("");
    ui->statusLabel->setProperty("state", "");
    ui->statusLabel->style()->polish(ui->statusLabel);

    setInfoText();
}

void TransferPage::onBeforeTransferInfo(const BeforeTransferInfo &info)
{
    ui->sendButton->setEnabled(info.isAllowed);
    setInfoText(info);

    if (info.to_acc.has_value() && info.isAllowed)
    {
        m_data.to_acc = info.to_acc.value();
        ui->statusLabel->setText(tr("> Всё корректно <"));
        ui->statusLabel->setProperty("state", "success");
        ui->statusLabel->style()->polish(ui->statusLabel);   
    }
    else
    {
        ui->statusLabel->setText(QString(tr("> Ошибка: %1 <")).arg(info.error));
        ui->statusLabel->setProperty("state", "error");
        ui->statusLabel->style()->polish(ui->statusLabel);
        setInfoText();
        QMessageBox::warning(this, tr("Ошибка"), info.error);
    }
}

void TransferPage::setInfoText()
{
    QString res = m_data.from_acc.iban.has_value() ?
        QString(tr("Отправитель: %1, %2\n")).arg(m_data.from_acc.id).arg(m_data.from_acc.iban.value()) :
        QString(tr("Отправитель: %1\n")).arg(m_data.from_acc.id);

    res += QString(tr(
        "Баланс: %1\n"
        "Валюта: %2"))
        .arg(m_data.from_acc.balance.value_or("0.00"),
             m_data.from_acc.currency);
    ui->infoEdit->setText(res);
}

void TransferPage::setInfoText(const BeforeTransferInfo &info)
{
    setInfoText();
    QString res = QString(tr(
        "\n--- Детали получателя ---\n"));
    if (info.to_acc.has_value())
    {
        QString recipient = info.to_acc.value().iban.has_value() ?
                            info.to_acc.value().iban.value() :
                                QString::number(info.to_acc.value().id);
        res += QString(tr("Получатель: %1\n")).arg(recipient);

        res += QString(tr(
            "Получатель: %1\n"
            "Валюта: %2\n"
            "Комиссия: %3\n"
            "Курс обмена: %4\n"
            "Будет зачислено: %5 %2")).arg(
            recipient,
            info.to_acc.value().currency,
            info.comission,
            info.exchangeRate,
            info.resultAmount);
    }
    else
        res += QString(tr("Получатель: не найден\n"));

    if (!info.isAllowed)
        res += QString(tr("\nОшибка: %1")).arg(info.error);

    ui->infoEdit->setText(ui->infoEdit->toPlainText() + res);
}

