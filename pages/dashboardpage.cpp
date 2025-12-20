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
