#include "transferpage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDoubleValidator>
#include <QMessageBox>



TransferPage::TransferPage(TransactionsService *trService, QWidget *parent)
    : QDialog(parent), ui(new Ui::TransferDialog), m_trService(trService)
{
    ui->setupUi(this);
    ui->amountEdit->setValidator(new QDoubleValidator(0.01, 1e12, 2, this));

    connect(ui->sendButton, &QPushButton::clicked, this,
    [this]{
        bool isNumCorrect = false;
        const double val = ui->amountEdit->text().toDouble(&isNumCorrect);
        if (isNumCorrect && val > 0)
        {
            m_data.from_amount = ui->amountEdit->text();
            m_data.description = ui->descriptionEdit->text() == QString()
                                     ? std::nullopt
                                     : std::make_optional(ui->descriptionEdit->text());
            m_trService->createTransferRequest(m_data);
        }
        else
            QMessageBox::warning(this, tr("Неверная сумма"), tr("Введите корректную положительную сумму"));
    });

    connect(ui->findButton, &QPushButton::clicked, this,
    [this]{
        if (ui->toEdit->text() != "")
        {
            ui->statusLabel->setText(tr("> Ожидание информации... <"));
            ui->statusLabel->setProperty("state", "loading");
            ui->statusLabel->style()->polish(ui->statusLabel);
            m_trService->createBeforeTrRequest(ui->toEdit->text());
        }
        else
            QMessageBox::warning(this, tr("Неверный получатель"), tr("Введите корректного получателя"));;
    });

    connect(ui->cancelButton, &QPushButton::clicked, this,
    [this]{
        emit pr_back();
    });

    connect(ui->toEdit, &QLineEdit::textChanged, this,
    [this]{
        ui->sendButton->setEnabled(false);
        setInfoText();
    });

    connect(m_trService, &TransactionsService::beforeTransferInfo,
            this, &TransferPage::onBeforeTransferInfo);
}

TransferPage::~TransferPage() { delete ui; }

void TransferPage::reset(const Models::Account &from)
{
    m_data.from_acc = from;
    ui->amountEdit->setText("0.00");
    ui->descriptionEdit->setText("");
    setInfoText();
    ui->sendButton->setEnabled(false);

    ui->statusLabel->setText("");
    ui->statusLabel->setProperty("state", "");
    ui->statusLabel->style()->polish(ui->statusLabel);
}

void TransferPage::onBeforeTransferInfo(const BeforeTransferInfo &info)
{
    if (!info.isError)
    {
        if (info.to_acc.has_value())
        {
            m_data.to_acc = info.to_acc.value();
            ui->sendButton->setEnabled(true);
            setInfoText(info);
        }
        else
        {
            ui->statusLabel->setText(tr("> Получатель не найден <"));
            ui->statusLabel->setProperty("state", "error");
            ui->statusLabel->style()->polish(ui->statusLabel);
            QMessageBox::warning(this, tr("Получатель не найден"), tr("Введите корректного получателя"));
        }
    }
    else
    {
        ui->statusLabel->setText(QString(tr("> Ошибка: %1 <")).arg(info.error));
        ui->statusLabel->setProperty("state", "error");
        ui->statusLabel->style()->polish(ui->statusLabel);
        QMessageBox::warning(this, tr("Ошибка поиска"), info.error);
    }
}

void TransferPage::onTransferResult(const std::optional<Models::Transaction> &tx)
{
    if (tx.has_value())
    {
        ui->statusLabel->setText(QString(tr("> Транзакция проведена успешно <")));
        ui->statusLabel->setProperty("state", "success");
        ui->statusLabel->style()->polish(ui->statusLabel);
    }
    else
    {
        ui->statusLabel->setText(QString(tr("> Ошибка: нет транзакции <")));
        ui->statusLabel->setProperty("state", "error");
        ui->statusLabel->style()->polish(ui->statusLabel);
    }
}

void TransferPage::setInfoText()
{
    if (m_data.from_acc.iban.has_value())
        ui->infoEdit->setText
        (
            QString(tr(
            "Отправитель: %1, %2\n"
            "Баланс: %3\n"
            "Валюта: %4"))
            .arg(m_data.from_acc.id)
            .arg(m_data.from_acc.iban.value(),
            m_data.from_acc.balance.value_or("0.00"),
            m_data.from_acc.currency)
        );
    else
        ui->infoEdit->setText
        (
            QString(tr(
            "Отправитель: %1\n"
            "Баланс: %2\n"
            "Валюта: %3"))
            .arg(m_data.from_acc.id).arg(m_data.from_acc.balance.value_or("0.00"), m_data.from_acc.currency)
        );
}

void TransferPage::setInfoText(const BeforeTransferInfo &info)
{
    setInfoText();
    if (info.to_acc->iban.has_value())
        ui->infoEdit->setText
        (
            ui->infoEdit->toPlainText() + QString(tr(
            "Получатель: %1\n"
            "Валюта: %2\n"
            "Комиссия: %3\n"
            "Курс обмена: %4\n"))
            .arg(info.to_acc->iban.value(), info.to_acc->currency, info.comission, info.exchangeRate)
        );
    else
        ui->infoEdit->setText
        (
            ui->infoEdit->toPlainText() + QString(tr(
            "Получатель: %1\n"
            "Валюта: %2\n"
            "Комиссия: %3\n"
            "Курс обмена: %4\n"))
            .arg(info.to_acc->id).arg(info.to_acc->currency, info.comission, info.exchangeRate)
        );
}

