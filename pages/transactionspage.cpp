#include "transactionspage.h"
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include "../constants.h"



TransactionsPage::TransactionsPage(TransactionsService *trService, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TransactionsPage)
    , m_trService(trService)
{
    ui->setupUi(this);
    setupConnections();
}

TransactionsPage::~TransactionsPage() { delete ui; }

void TransactionsPage::setupConnections()
{
    connect(ui->backButton, &QPushButton::clicked, this,
    [this]{
        emit pr_dashboard();
    });

    connect(ui->refreshButton, &QPushButton::clicked, this,
    [this]{
        refreshTransactions();
    });

    connect(ui->pageSpinBox, &QSpinBox::valueChanged, this,
    [this](int){
        refreshTransactions();
    });

    connect(ui->limitComboBox, &QComboBox::currentTextChanged, this,
    [this](QString){
        refreshTransactions();
    });

    connect(m_trService, &TransactionsService::transactionsUpdated,
            this, &TransactionsPage::onTransactionsUpdated);
    connect(m_trService, &TransactionsService::transactionsFailed,
            this, &TransactionsPage::onTransactionsFailed);
    connect(m_trService, &TransactionsService::transactionCreated,
            this, &TransactionsPage::onTransactionCreated);

}

void TransactionsPage::refreshTransactions()
{
    showLoading(tr("Загрузка транзакций..."));

    int currentPage = ui->pageSpinBox->value();
    int currentLimit = ui->limitComboBox->currentText().toInt();
    qDebug() << "Page: " << currentPage << "Limit: " << currentLimit;
    m_trService->createTrListRequest(currentLimit, currentPage);
}

void TransactionsPage::onTransactionsUpdated(const QList<Models::Transaction> &transactions)
{
    ui->transactionsList->clear();

    for (const auto &tx : transactions)
    {
        QString direction;
        if (tx.counterparty_account_id.has_value()) {
            direction = tr("Счёт #%1 ➔ Счёт #%2")
                            .arg(tx.account_id)
                            .arg(*tx.counterparty_account_id);
        } else {
            direction = tr("Счёт #%1").arg(tx.account_id);
        }

        QString icon = "•";
        QString sign = "";
        if (tx.type == "deposit") {
            icon = "➕"; sign = "+";
        } else if (tx.type == "withdrawal") {
            icon = "➖"; sign = "-";
        } else if (tx.type == "transfer") {
            icon = "⇄";
        }

        QString dateStr = tx.created_at.has_value()
                              ? tx.created_at->toString("dd.MM HH:mm")
                              : "--.--";

        // [Иконка] [Тип/Описание] | [Направление] | [Сумма]
        const QString line = QString("%1 %2 | %3 | %4%5 %6 | %7")
                                 .arg(icon,
                                      tx.description.value_or(tx.type).leftJustified(15, ' '),
                                      direction.leftJustified(30, ' '),
                                      sign, tx.amount,
                                      tx.currency.isEmpty() ? Enums::toStr(Enums::Currency::BYN) + "?" : tx.currency,
                                      dateStr);

        QListWidgetItem *item = new QListWidgetItem(line);

        if (tx.type == "deposit") item->setForeground(QColor(0x2b9348));
        else if (tx.type == "withdrawal") item->setForeground(QColor(0xe63946));

        ui->transactionsList->addItem(item);
    }

    if (transactions.isEmpty())
    {
        ui->statusLabel->setText(tr("> Нет транзакций <"));
        ui->statusLabel->setProperty("state", "empty");
        ui->statusLabel->style()->polish(ui->statusLabel);
    }
    else
    {
        ui->statusLabel->clear();
        ui->statusLabel->setProperty("state", "");
        ui->statusLabel->style()->polish(ui->statusLabel);
    }
    ui->refreshButton->setEnabled(true);
}

void TransactionsPage::onTransactionsFailed(const QString &reason)
{
    ui->statusLabel->setText(tr("> Ошибка: %1 <").arg(reason));
    ui->statusLabel->setProperty("state", "error");
    ui->statusLabel->style()->polish(ui->statusLabel);
    ui->refreshButton->setEnabled(true);
}

void TransactionsPage::onTransactionCreated(const Models::Transaction &transaction)
{
    ui->statusLabel->setText(tr("> Транзакция успешно создана <"));
    ui->statusLabel->setProperty("state", "success");
    ui->statusLabel->style()->polish(ui->statusLabel);
    ui->refreshButton->setEnabled(true);
    refreshTransactions();
}

void TransactionsPage::showLoading(const QString &message)
{
    ui->statusLabel->setText(message.isEmpty() ? tr("> Загрузка... <") : message);
    ui->statusLabel->setProperty("state", "loading");
    ui->statusLabel->style()->polish(ui->statusLabel);
    ui->refreshButton->setEnabled(false);
}

