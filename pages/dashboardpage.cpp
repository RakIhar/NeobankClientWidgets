#include "dashboardpage.h"
#include <QPushButton>

DashboardPage::DashboardPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DashboardPage)
{
    ui->setupUi(this);
    setupConnections();
}

DashboardPage::~DashboardPage() { delete ui; }


void DashboardPage::setupConnections()
{
    connect(ui->accountsButton, &QPushButton::clicked, this,
    [this]{
        emit pr_accounts();
    });

    connect(ui->transactionsButton, &QPushButton::clicked, this,
    [this]{
        emit pr_transactions();
    });

    connect(ui->logoutButton, &QPushButton::clicked, this,
    [this]{
        emit r_logout();
    });
}

//Отложено до лучших времён
// void DashboardPage::computeAndShowTotal(const QString &base)
// {
//     QMap<QString, qint64> sums;
//     for (const auto &acc : std::as_const(m_accounts)) {
//         bool ok = false;
//         double amount = acc.balance.has_value() ? acc.balance.value().toDouble(&ok) : 0.0;
//         if (!ok) continue;
//         qint64 cents = static_cast<qint64>(std::llround(amount * 100.0));
//         sums[acc.currency] = sums.value(acc.currency, 0) + cents;
//     }
//     QStringList parts;
//     for (auto it = sums.begin(); it != sums.end(); ++it) {
//         parts << QString("%1: %2").arg(it.key()).arg(Money::fromCents(it.value()));
//     }
//     ui->balanceLabel->setText(parts.join("; "));
// }

// void DashboardPage::onAccountsUpdated(const QList<Models::Account> &accounts)
// {
//     m_accounts = accounts;
//     computeAndShowTotal();
// }

// void DashboardPage::update()
// {
//    //послать count request, потом забрать все страницы и посчитать баланс
//    //или добавить API для получения всех аккаунтов за раз
// }
