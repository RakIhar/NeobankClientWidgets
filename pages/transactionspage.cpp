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
    ui->transactionsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

    connect(m_trService, &TransactionsService::transactionsList,
        this, &TransactionsPage::onTransactionsUpdated);

    connect(m_trService, &TransactionsService::transactionsFailed,
            this, &TransactionsPage::onTransactionsFailed);

    connect(m_trService, &TransactionsService::transactionCreated,
            this, &TransactionsPage::onTransactionCreated);

    connect(m_trService, &TransactionsService::transactionsCount,
        this, &TransactionsPage::onTransactionsCount);
}

void TransactionsPage::refreshTransactions()
{
    showLoading(tr("Загрузка транзакций..."));

    int currentPage = ui->pageSpinBox->value() - 1;
    int currentLimit = ui->limitComboBox->currentText().toInt();
    qDebug() << "Page: " << currentPage << "Limit: " << currentLimit;
    m_trService->transactionsListRequest(currentLimit, currentPage);
}

void TransactionsPage::onTransactionsUpdated(const QList<Models::Transaction> &transactions)
{
    ui->transactionsTable->clearContents();
    ui->transactionsTable->setRowCount(transactions.size());
    ui->transactionsTable->setHorizontalHeaderLabels({tr("Дата"), tr("Тип"), tr("Счёта"), tr("Сумма"), tr("Валюта")});
    int row = 0;
    for (const auto &tx : transactions)
    {
        QString direction;
        QString selfLabel = QString::number(tx.account_id);
        QString cpLabel = tx.counterparty_account_id.has_value() ? QString::number(tx.counterparty_account_id.value()) : QString();
        // prefer IBANs from metadata when present
        if (tx.metadata.has_value()) {
            QJsonObject md = tx.metadata.value();
            if (md.contains("self_iban") && !md.value("self_iban").toString().isEmpty())
                selfLabel = QString("%1 (%2)").arg(selfLabel).arg(md.value("self_iban").toString());
            if (md.contains("counterparty_iban") && !md.value("counterparty_iban").toString().isEmpty() && !cpLabel.isEmpty())
                cpLabel = QString("%1 (%2)").arg(cpLabel).arg(md.value("counterparty_iban").toString());
        }
        if (!cpLabel.isEmpty())
            direction = tr("%1 ➔ %2").arg(selfLabel).arg(cpLabel);
        else
            direction = selfLabel;

        QString dateStr = tx.created_at.has_value() ? tx.created_at->toString("dd.MM HH:mm") : "--.--";

        QTableWidgetItem *dateItem = new QTableWidgetItem(dateStr);
        QTableWidgetItem *typeItem = new QTableWidgetItem(tx.description.value_or(tx.type));
        QTableWidgetItem *dirItem  = new QTableWidgetItem(direction);
        QTableWidgetItem *amountItem = new QTableWidgetItem(tx.amount);
        QTableWidgetItem *curItem = new QTableWidgetItem(tx.currency.isEmpty() ? tr("?") : tx.currency);

        // make items read-only
        dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);
        typeItem->setFlags(typeItem->flags() & ~Qt::ItemIsEditable);
        dirItem->setFlags(dirItem->flags() & ~Qt::ItemIsEditable);
        amountItem->setFlags(amountItem->flags() & ~Qt::ItemIsEditable);
        curItem->setFlags(curItem->flags() & ~Qt::ItemIsEditable);

        // show metadata (commission/exchange/result) as tooltip on amount
        if (tx.metadata.has_value()) {
            QJsonObject md = tx.metadata.value();
            QStringList parts;
            if (md.contains(toStr(JsonField::Comission))) parts << md.value(toStr(JsonField::Comission)).toString();
            if (md.contains(toStr(JsonField::ExchangeRate))) parts << tr("rate:") + md.value(toStr(JsonField::ExchangeRate)).toString();
            if (md.contains(toStr(JsonField::Amount))) parts << tr("final:") + md.value(toStr(JsonField::Amount)).toString();
            if (!parts.isEmpty()) amountItem->setToolTip(parts.join("; "));
        }

        // if metadata contains counterparty IBAN, prefer to display it
        if (tx.metadata.has_value()) {
            QJsonObject md = tx.metadata.value();
            if (md.contains("counterparty_iban") && !md.value("counterparty_iban").toString().isEmpty()) {
                QString cp = md.value("counterparty_iban").toString();
                dirItem->setText(tr("%1 ➔ %2").arg(tx.account_id).arg(cp));
            }
        }

        ui->transactionsTable->setItem(row, 0, dateItem);
        ui->transactionsTable->setItem(row, 1, typeItem);
        ui->transactionsTable->setItem(row, 2, dirItem);
        ui->transactionsTable->setItem(row, 3, amountItem);
        ui->transactionsTable->setItem(row, 4, curItem);
        row++;
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

void TransactionsPage::onTransactionsCount(int total, int page, int limit)
{
    int pages = limit > 0 ? ((total + limit - 1) / limit) : 1;
    ui->pageSpinBox->setMaximum(std::max(1, pages));
    ui->statusLabel->setText(tr("Всего: %1 записей, стр %2/%3").arg(total).arg(page+1).arg(pages));
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

