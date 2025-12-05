#include "dashboardpage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>

DashboardPage::DashboardPage(QWidget *parent)
    : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);

    // Заголовок
    m_welcomeLabel = new QLabel(tr("Добро пожаловать!"), this);
    m_welcomeLabel->setStyleSheet("font-size: 20px; font-weight: bold; padding: 10px;");
    mainLayout->addWidget(m_welcomeLabel);

    // Баланс
    auto *balanceGroup = new QGroupBox(tr("Общий баланс"), this);
    auto *balanceLayout = new QVBoxLayout(balanceGroup);
    m_balanceLabel = new QLabel(tr("0.00 ₽"), this);
    m_balanceLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: #2e7d32; padding: 20px;");
    balanceLayout->addWidget(m_balanceLabel);
    mainLayout->addWidget(balanceGroup);

    // Быстрые действия
    auto *actionsGroup = new QGroupBox(tr("Быстрые действия"), this);
    auto *actionsLayout = new QGridLayout(actionsGroup);

    m_accountsButton = new QPushButton(tr("Мои счета"), this);
    m_accountsButton->setStyleSheet("padding: 15px; font-size: 14px; min-height: 50px;");
    actionsLayout->addWidget(m_accountsButton, 0, 0);

    m_transactionsButton = new QPushButton(tr("Транзакции"), this);
    m_transactionsButton->setStyleSheet("padding: 15px; font-size: 14px; min-height: 50px;");
    actionsLayout->addWidget(m_transactionsButton, 0, 1);

    mainLayout->addWidget(actionsGroup);

    mainLayout->addStretch();

    // Кнопка выхода
    m_logoutButton = new QPushButton(tr("Выйти"), this);
    m_logoutButton->setStyleSheet("padding: 10px; font-size: 14px;");
    mainLayout->addWidget(m_logoutButton);

    // Подключения
    connect(m_accountsButton, &QPushButton::clicked, this, &DashboardPage::onAccountsClicked);
    connect(m_transactionsButton, &QPushButton::clicked, this, &DashboardPage::onTransactionsClicked);
    connect(m_logoutButton, &QPushButton::clicked, this, &DashboardPage::onLogoutClicked);
}

void DashboardPage::onAccountsClicked()
{
    emit showAccounts();
}

void DashboardPage::onTransactionsClicked()
{
    emit showTransactions();
}

void DashboardPage::onLogoutClicked()
{
    emit logout();
}

