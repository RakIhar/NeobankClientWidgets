#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "services/authservice.h"
#include "services/accountsservice.h"
#include "services/transactionsservice.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QJsonObject>
#include "constants.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_client(std::make_unique<SocketWrapper>(this))
    , m_stackedWidget(nullptr)
    , m_authService(nullptr)
    , m_accountsService(nullptr)
    , m_transactionsService(nullptr)
{
    ui->setupUi(this);
    setWindowTitle(tr("NeoBank Client"));

    setupServices();
    setupPages();

    connect(m_client.get(), &SocketWrapper::received,
            this, &MainWindow::routeMessage);

    showPage(PageConnect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupPages()
{
    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

    m_pages.connectPage      = new ConnectPage(this);
    m_pages.loginPage        = new LoginPage(m_authService, this);
    m_pages.dashboardPage    = new DashboardPage(this);
    m_pages.accountsPage     = new AccountsPage(m_accountsService, m_transactionsService, this);
    m_pages.registrationPage = new RegistrationPage(m_authService, this);
    m_pages.transactionsPage = new TransactionsPage(m_transactionsService, this);
    m_pages.transferPage     = new TransferPage(m_transactionsService, this);

    m_stackedWidget->addWidget(m_pages.connectPage);
    m_stackedWidget->addWidget(m_pages.loginPage);
    m_stackedWidget->addWidget(m_pages.dashboardPage);
    m_stackedWidget->addWidget(m_pages.accountsPage);
    m_stackedWidget->addWidget(m_pages.transactionsPage);
    m_stackedWidget->addWidget(m_pages.registrationPage);
    m_stackedWidget->addWidget(m_pages.transferPage);
    setupSwaps();

    connect(m_pages.connectPage, &ConnectPage::r_connect,
    this, [this](QString host, quint16 port){
        m_client->connect(host, port);
    });
    connect(m_client.get(), &SocketWrapper::errorOccurred,
            m_pages.connectPage, &ConnectPage::onSocketError);
}

void MainWindow::setupServices()
{
    SendDelegate send = [this](const QByteArray& data){
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (!doc.isObject()) return;

        if (!doc.isNull()) {
            qDebug().noquote() << "Sent JSON:\n" << doc.toJson(QJsonDocument::Indented);
        } else
            qDebug() << "Sent:\n" << data;

        m_client->send(data);
    };
    AuthDelegate authenticate = [this](QJsonObject &request) {
        m_authService->setAuthentificationData(request);
    };
    m_authService = new AuthService(send, this);
    m_accountsService = new AccountsService(send, authenticate, this);
    m_transactionsService = new TransactionsService(send, authenticate, this);
}

void MainWindow::setupSwaps()
{
    connect(m_pages.loginPage, &LoginPage::pr_registration, this,
    [this]{
        m_pages.registrationPage->reset();
        showPage(PageRegistration);
    });
    connect(m_pages.registrationPage, &RegistrationPage::pr_login, this,
    [this]{
        m_pages.loginPage->reset();
        showPage(PageLogin);
    });
    connect(m_pages.dashboardPage, &DashboardPage::pr_accounts, this,
    [this]{
        m_pages.accountsPage->refreshAccounts();
        showPage(PageAccounts);
    });
    connect(m_pages.dashboardPage, &DashboardPage::pr_transactions, this,
    [this]{
        m_pages.transactionsPage->refreshTransactions();
        showPage(PageTransactions);
    });
    connect(m_pages.accountsPage, &AccountsPage::pr_dashboard, this,
    [this]{
        showPage(PageDashboard);
    });
    connect(m_pages.accountsPage, &AccountsPage::pr_transfer, this,
    [this](Models::Account acc){
        m_pages.transferPage->reset(acc);
        showPage(PageTransfer);
    });
    connect(m_pages.transactionsPage, &TransactionsPage::pr_dashboard, this,
    [this]{
        showPage(PageDashboard);
    });
    connect(m_pages.transferPage, &TransferPage::pr_back, this,
    [this]{
        m_pages.accountsPage->refreshAccounts();
        showPage(PageAccounts);
    });

    connect(m_client.get(), &SocketWrapper::connected, this,
    [this]{
        m_pages.connectPage->reset();
        m_pages.loginPage->reset();
        showPage(PageLogin);
    });
    connect(m_authService, &AuthService::loginSuccess, this,
    [this]{
        showPage(PageDashboard);
    });
    connect(m_pages.dashboardPage, &DashboardPage::r_logout,this,
    [this]{
        if (m_client) {
            m_client->disconnect();
        }
        m_pages.connectPage->reset();
        showPage(PageConnect);
    });
}

void MainWindow::routeMessage(const QByteArray &msg)
{
    QJsonDocument doc = QJsonDocument::fromJson(msg);
    if (!doc.isObject()) return;

    if (!doc.isNull()) {
        qDebug().noquote() << "Received JSON:\n" << doc.toJson(QJsonDocument::Indented);
    } else
        qDebug() << "Received:\n" << msg;

    QJsonObject obj = doc.object();
    QString type = obj.value("type").toString();
    if (type == "login" || type == "register")
        m_authService->handleMessage(msg);
    else if (type.startsWith("account"))
        m_accountsService->handleMessage(msg);
    else if (type.startsWith("transaction"))
        m_transactionsService->handleMessage(msg);
    else
        qDebug() << "Unknown message type" << type;
}

