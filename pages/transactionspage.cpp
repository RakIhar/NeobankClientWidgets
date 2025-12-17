#include "transactionspage.h"
#include "../services/transactionsservice.h"

#include <QListWidget>
#include <QPushButton>
#include <QLabel>

TransactionsPage::TransactionsPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TransactionsPage)
{
    ui->setupUi(this);
    setupConnections();
}

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
}

void TransactionsPage::refreshTransactions()
{
    showLoading(tr("Загрузка транзакций..."));
    emit r_transactions();
}

void TransactionsPage::onTransactionsUpdated(const QList<TransactionInfo> &transactions)
{
    ui->transactionsList->clear();
    for (const auto &tx : transactions)
    {
        const QString line = tr("%1 • %2 %3 • %4")
                                 .arg(tx.createdAt.isEmpty() ? tr("Дата неизвестна") : tx.createdAt)
                                 .arg(tx.amount)
                                 .arg(tx.currency.isEmpty() ? QStringLiteral("₽") : tx.currency)
                                 .arg(tx.description.isEmpty() ? tx.type : tx.description);
        ui->transactionsList->addItem(line);
    }

    if (transactions.isEmpty())
    {
        ui->statusLabel->setText(tr("> Нет транзакций <"));
        ui->statusLabel->setStyleSheet(
            "font-size: 12px; "
            "color: #ff6b6b; "
            "padding: 20px; "
            "background: transparent;"
            "letter-spacing: 2px;"
        );
    }
    else
    {
        ui->statusLabel->clear();
    }
    ui->refreshButton->setEnabled(true);
}

void TransactionsPage::onTransactionsFailed(const QString &reason)
{
    ui->statusLabel->setText(tr("❌ %1").arg(reason));
    ui->statusLabel->setStyleSheet(
        "font-size: 14px; "
        "color: #ff6b6b; "
        "padding: 16px; "
        "background: transparent;"
    );
    ui->refreshButton->setEnabled(true);
}
//CHECK
void TransactionsPage::onTransactionCreated(const TransactionInfo &transaction)
{
    Q_UNUSED(transaction);
    ui->statusLabel->setText(tr("✅ Транзакция успешно создана"));
    ui->statusLabel->setStyleSheet(
        "font-size: 14px; "
        "color: #3ac569; "
        "padding: 16px; "
        "background: transparent;"
    );
    ui->refreshButton->setEnabled(true);
    // Автообновим список транзакций
    refreshTransactions();
}

void TransactionsPage::showLoading(const QString &message)
{
    ui->statusLabel->setText(message.isEmpty() ? tr("> Загрузка... <") : message);
    ui->statusLabel->setStyleSheet(
        "font-size: 14px; "
        "color: #4facfe; "
        "padding: 16px; "
        "background: transparent;"
    );
    ui->refreshButton->setEnabled(false);
}

