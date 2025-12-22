#include "accountspage.h"
#include <QInputDialog>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include "../constants.h"
#include "../converters.h"

AccountsPage::AccountsPage(AccountsService *accService, TransactionsService *trService, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountsPage)
    , m_accService(accService)
    , m_trService(trService)
{
    ui->setupUi(this);
    setupConnections();

    QMetaEnum metaEnum = QMetaEnum::fromType<Enums::Currency>();
    ui->currencyComboBox->clear();
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        QString key = metaEnum.key(i);
        Enums::Currency value = static_cast<Enums::Currency>(metaEnum.value(i));
        ui->currencyComboBox->addItem(key, QVariant::fromValue(value));
    }
}

AccountsPage::~AccountsPage() { delete ui; }

void AccountsPage::setupConnections()
{
    connect(ui->pageSpinBox, &QSpinBox::valueChanged, this,
    [this](int){
        refreshAccounts();
    });

    connect(ui->limitComboBox, &QComboBox::currentTextChanged, this,
    [this](QString){
        refreshAccounts();
    });

    connect(ui->backButton, &QPushButton::clicked, this,
    [this]{
        emit pr_dashboard();
    });

    connect(ui->refreshButton, &QPushButton::clicked, this,
    [this]{
        refreshAccounts();
    });

    connect(ui->createButton, &QPushButton::clicked, this,
    [this]{
        m_accService->accountCreateRequest(ui->currencyComboBox->currentData().value<Enums::Currency>());
    });

    connect(ui->accountsTable, &QTableWidget::cellDoubleClicked, this,
    [this](int row, int){
        if (row >= 0 && row < m_accounts.size())
            emit pr_transfer(m_accounts.at(row));
    });

    connect(ui->testCreditButton, &QPushButton::clicked,
            this, &AccountsPage::onTestCredit);

    connect(ui->deleteButton, &QPushButton::clicked,
            this, &AccountsPage::onDeleteAccount);

    connect(m_accService, &AccountsService::accountsList,
            this, &AccountsPage::onAccountsUpdated);

    connect(m_accService, &AccountsService::accountsFailed,
            this, &AccountsPage::onAccountsFailed);

    connect(m_accService, &AccountsService::accountCreated, this,
    [this](const Models::Account&){
        refreshAccounts();
    });

    connect(m_accService, &AccountsService::accountDeleted, this,
    [this](){
        refreshAccounts();
    });

    connect(m_accService, &AccountsService::accountsCount,
            this, &AccountsPage::onAccountsCount);
}

void AccountsPage::onTestCredit()
{  
    const int row = ui->accountsTable->currentRow();

    if (row >= 0 && row < m_accounts.size())
    {
        bool isCorrect = false;
        const QString amount = QInputDialog::getText(this,  tr("Тестовое начисление"), tr("Сумма:"), QLineEdit::Normal, "100", &isCorrect);
        if (isCorrect)
        {
            const Models::Account acc = m_accounts.at(row);
            std::pair<qint64, bool> amountPair = Money::toCents(amount, true);
            if (amountPair.first && amountPair.second)
            {
                CreditData crData;
                crData.acc = acc;
                crData.amount = Money::fromCents(amountPair.first);
                m_trService->creditRequest(crData);
            }
            else
                onAccountsFailed(tr("Некорректная сумма для тестового начисления"));
        }
    }
    else
        onAccountsFailed(tr("Неверный счёт"));
}

void AccountsPage::onDeleteAccount()
{
    const int row = ui->accountsTable->currentRow();

    if (row >= 0 && row < m_accounts.size())
    {
        const Models::Account acc = m_accounts.at(row);
        std::pair<qint64, bool> bal = Money::toCents(acc.balance.value_or("0.00"));
        if (!bal.second)
            onAccountsFailed(tr("Некорректный баланс"));
        else if (bal.first)
            onAccountsFailed(tr("Нельзя удалить аккаунт с ненулевым балансом"));
        else
            m_accService->accountDeleteRequest(acc);
    }
    else
        onAccountsFailed(tr("Неверный счёт"));
}

void AccountsPage::refreshAccounts()
{
    showLoading(tr("Загрузка счетов..."));

    int currentPage = ui->pageSpinBox->value() - 1;
    int currentLimit = ui->limitComboBox->currentText().toInt();
    qDebug() << "Page: " << currentPage << "Limit: " << currentLimit;
    m_accService->accountsListRequest(currentLimit, currentPage);
}

void AccountsPage::onAccountsUpdated(const QList<Models::Account> &accounts)
{
    ui->accountsTable->clearContents();
    ui->accountsTable->setRowCount(accounts.size());
    ui->accountsTable->setHorizontalHeaderLabels({tr("ID"), tr("IBAN"), tr("Баланс"), tr("Валюта"), tr("Статус")});
    m_accounts = accounts;
    int row = 0;
    for (const auto &acc : accounts)
    {
        QString ibanStr = acc.iban.has_value() ? *acc.iban : tr("Нет IBAN");
        Enums::Currency currEnum = Enums::fromStr(acc.currency, Enums::Currency::BYN);
        QString symbol = Enums::toSymbol(currEnum);
        if (symbol.isEmpty()) symbol = acc.currency;
        QString statusStr = acc.status.value_or("active");

        QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(acc.id));
        QTableWidgetItem *ibanItem = new QTableWidgetItem(ibanStr);
        QTableWidgetItem *balItem = new QTableWidgetItem(acc.balance.value_or("0.00"));
        QTableWidgetItem *curItem = new QTableWidgetItem(symbol);
        QTableWidgetItem *statusItem = new QTableWidgetItem(statusStr);

        if (statusStr != "active") {
            idItem->setForeground(Qt::gray);
            ibanItem->setForeground(Qt::gray);
            balItem->setForeground(Qt::gray);
            statusItem->setToolTip(tr("Счет заморожен или неактивен"));
        }

        ui->accountsTable->setItem(row, 0, idItem);
        ui->accountsTable->setItem(row, 1, ibanItem);
        ui->accountsTable->setItem(row, 2, balItem);
        ui->accountsTable->setItem(row, 3, curItem);
        ui->accountsTable->setItem(row, 4, statusItem);
        row++;
    }

    if (accounts.isEmpty())
    {
        ui->statusLabel->setText(tr("> Аккаунты не найдены <"));
        ui->statusLabel->setProperty("state", "empty");
    }
    else
    {
        ui->statusLabel->clear();
        ui->statusLabel->setProperty("state", "");
    }
    ui->statusLabel->style()->polish(ui->statusLabel);
    ui->refreshButton->setEnabled(true);
}

void AccountsPage::onAccountsFailed(const QString &reason)
{
    ui->statusLabel->setText(tr("> Ошибка: %1 <").arg(reason.toUpper()));
    ui->statusLabel->setProperty("state", "error");
    ui->statusLabel->style()->polish(ui->statusLabel);
    ui->refreshButton->setEnabled(true);
}

void AccountsPage::showLoading(const QString &message)
{
    ui->statusLabel->setText(message.isEmpty() ? tr("> Загрузка... <") : message.toUpper());
    ui->statusLabel->setProperty("state", "loading");
    ui->statusLabel->style()->polish(ui->statusLabel);
    ui->refreshButton->setEnabled(false);
}

void AccountsPage::onAccountsCount(int total, int page, int limit)
{
    int pages = limit > 0 ? ((total + limit - 1) / limit) : 1;
    ui->pageSpinBox->setMaximum(std::max(1, pages));
    ui->statusLabel->setText(tr("Всего счетов: %1, стр %2/%3").arg(total).arg(page+1).arg(pages));
}

