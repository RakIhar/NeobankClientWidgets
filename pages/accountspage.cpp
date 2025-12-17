#include "accountspage.h"
#include "../services/accountsservice.h"
#include "transferdialog.h"
#include <QInputDialog>
#include <QListWidgetItem>

#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include "../constants.h"

AccountsPage::AccountsPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountsPage)
{
    ui->setupUi(this);
    setupConnections();
}

void AccountsPage::setupConnections()
{
    connect(ui->backButton, &QPushButton::clicked, this,
    [this]{
        emit pr_dashboard();
    });

    connect(ui->refreshButton, &QPushButton::clicked, this,
    [this]{
        refreshAccounts();
    });
    ///CHECK
    connect(ui->accountsList, &QListWidget::itemDoubleClicked, this,
    [this](QListWidgetItem *item){
        const int row = ui->accountsList->row(item);
        if (row < 0 || row >= m_accounts.size())
            return;
        const AccountInfo acc = m_accounts.at(row);
        TransferDialog dlg(this);
        dlg.setFromAccount(acc.id.isEmpty() ? acc.iban : acc.id);
        if (dlg.exec() == QDialog::Accepted) {
            const auto data = dlg.resultData();
            emit r_transferRequested(acc.id.isEmpty() ? acc.iban : acc.id,
                                     data.toAccount,
                                     data.amount,
                                     Enums::fromStr(data.currency, Enums::Currency::BYN),
                                     data.description);
        }
    });

    connect(ui->createButton, &QPushButton::clicked, this, [this]{
        emit r_createAccount(Enums::Currency::BYN); //TODO CHECK добавить новые валюты
    });

    connect(ui->testCreditButton, &QPushButton::clicked, this, [this]{
        const auto current = ui->accountsList->currentItem();
        if (!current) {
            onAccountsFailed(tr("Выберите счёт перед тестовым начислением"));
            return;
        }
        const int row = ui->accountsList->row(current);
        if (row < 0 || row >= m_accounts.size()) {
            onAccountsFailed(tr("Неверный счёт"));
            return;
        }
        bool ok = false;
        const QString amount = QInputDialog::getText(this, tr("Тестовое начисление"), tr("Сумма:"), QLineEdit::Normal, "100", &ok);
        if (!ok || amount.isEmpty()) return;
        const AccountInfo acc = m_accounts.at(row);
        emit r_testCreditRequested(acc.id.isEmpty() ? acc.iban : acc.id, amount);
    });
    ///
}

void AccountsPage::refreshAccounts()
{
    showLoading(tr("Загрузка счетов..."));
    emit r_accounts();
}

void AccountsPage::onAccountsUpdated(const QList<AccountInfo> &accounts)
{
    ui->accountsList->clear();
    m_accounts = accounts; //CHECK
    for (const auto &acc : accounts)
    {
        const QString text = tr("Счет %1 • %2 %3 (%4)")
                                 .arg(acc.iban.isEmpty() ? acc.id : acc.iban,
                                      acc.balance,
                                      acc.currency.isEmpty() ? QStringLiteral("₽") : acc.currency,
                                      acc.status);
        ui->accountsList->addItem(text);
    }

    if (accounts.isEmpty())
    {
        ui->statusLabel->setText(tr("> Аккаунты не найдены <"));
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

void AccountsPage::onAccountsFailed(const QString &reason)
{
    ui->statusLabel->setText(tr("> Ошибка: %1 <").arg(reason.toUpper()));
    ui->statusLabel->setStyleSheet(
        "font-size: 12px; "
        "color: #ff6b6b; "
        "padding: 20px; "
        "background: transparent;"
        "letter-spacing: 2px;"
    );
    ui->refreshButton->setEnabled(true);
}

void AccountsPage::showLoading(const QString &message)
{
    ui->statusLabel->setText(message.isEmpty() ? tr("> Загрузка... <") : message.toUpper());
    ui->statusLabel->setStyleSheet(
        "font-size: 12px; "
        "color: #4facfe; "
        "padding: 20px; "
        "background: transparent;"
        "letter-spacing: 2px;"
    );
    ui->refreshButton->setEnabled(false);
}

