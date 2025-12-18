#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "network/socketwrapper.h"
#include "pages/connectpage.h"
#include "pages/loginpage.h"
#include "pages/dashboardpage.h"
#include "pages/accountspage.h"
#include "pages/transactionspage.h"
#include "pages/registrationpage.h"
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
    , m_connectPage(nullptr)
    , m_loginPage(nullptr)
    , m_dashboardPage(nullptr)
    , m_accountsPage(nullptr)
    , m_transactionsPage(nullptr)
    , m_registrationPage(nullptr)
    , m_authService(nullptr)
    , m_accountsService(nullptr)
    , m_transactionsService(nullptr)
{
    ui->setupUi(this);
    setWindowTitle(tr("NeoBank Client"));
    setupPagesServices();
    setupPageSwapConnections();
    setupRequestConnections();
    setupConnectionsFromServicesToPages();
    connect(m_client.get(), &SocketWrapper::received, this, &MainWindow::routeMessage);
    showPage(PageConnect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupPagesServices()
{
    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

    m_connectPage = new ConnectPage(this);
    m_loginPage = new LoginPage(this);
    m_dashboardPage = new DashboardPage(this);
    m_accountsPage = new AccountsPage(this);
    m_registrationPage = new RegistrationPage(this);
    m_transactionsPage = new TransactionsPage(this);

    m_authService = new AuthService(this);
    m_accountsService = new AccountsService(this);
    m_transactionsService = new TransactionsService(this);

    m_stackedWidget->addWidget(m_connectPage);
    m_stackedWidget->addWidget(m_loginPage);
    m_stackedWidget->addWidget(m_dashboardPage);
    m_stackedWidget->addWidget(m_accountsPage);
    m_stackedWidget->addWidget(m_transactionsPage);
    m_stackedWidget->addWidget(m_registrationPage);
}

void MainWindow::setupPageSwapConnections()
{
    connect(m_client.get(), &SocketWrapper::connected, this,
    [this](){
        m_connectPage->reset();
        m_loginPage->reset();
        showPage(PageLogin);
    });
    connect(m_authService, &AuthService::loginSuccess, this,
    [this]{
        showPage(PageDashboard);
    });

    connect(m_loginPage, &LoginPage::pr_registration, this,
    [this]{
        m_registrationPage->reset();
        showPage(PageRegistration);
    });
    connect(m_registrationPage, &RegistrationPage::pr_login, this,
    [this]{
        m_loginPage->reset();
        showPage(PageLogin);
    });
    connect(m_dashboardPage, &DashboardPage::pr_accounts, this,
    [this]{
        m_accountsPage->refreshAccounts();
        showPage(PageAccounts);
    });
    connect(m_dashboardPage, &DashboardPage::pr_transactions, this,
    [this]{
        m_transactionsPage->refreshTransactions();
        showPage(PageTransactions);
    });
    connect(m_accountsPage, &AccountsPage::pr_dashboard, this,
    [this]{
        showPage(PageDashboard);
    });
    connect(m_transactionsPage, &TransactionsPage::pr_dashboard, this,
    [this]{
        showPage(PageDashboard);
    });
}

void MainWindow::setupRequestConnections()
{
    connect(m_connectPage, &ConnectPage::r_connect,
            this, &MainWindow::onRequestConnect);
    connect(m_loginPage, &LoginPage::r_login,
            this, &MainWindow::onRequestLogin);
    connect(m_registrationPage, &RegistrationPage::r_registration,
            this, &MainWindow::onRequestRegistration);
    connect(m_dashboardPage, &DashboardPage::r_logout,
            this, &MainWindow::onRequestLogout);
    connect(m_accountsPage, &AccountsPage::r_accounts,
            this, &MainWindow::onRequestAccountsList);
    connect(m_transactionsPage, &TransactionsPage::r_transactions,
            this, &MainWindow::onRequestTransactionsList);
    connect(m_accountsPage, &AccountsPage::r_transferRequested,
        this, &MainWindow::onRequestCreateTransaction);
    connect(m_accountsPage, &AccountsPage::r_createAccount,
        this, &MainWindow::onRequestCreateAccount);
    connect(m_accountsPage, &AccountsPage::r_testCreditRequested,
        this, &MainWindow::onRequestTestCredit);
}

void MainWindow::setupConnectionsFromServicesToPages()
{
    connect(m_client.get(), &SocketWrapper::errorOccurred,
            m_connectPage, &ConnectPage::onSocketError);

    connect(m_authService, &AuthService::loginFailed,
            m_loginPage, &LoginPage::onLoginError);

    connect(m_authService, &AuthService::registerSuccess,
            m_registrationPage, &RegistrationPage::onRegistrationSuccess);
    connect(m_authService, &AuthService::registerFailed,
            m_registrationPage, &RegistrationPage::onRegistrationError);

    connect(m_accountsService, &AccountsService::accountsUpdated,
        m_accountsPage, &AccountsPage::onAccountsUpdated);
    connect(m_accountsService, &AccountsService::accountsFailed,
        m_accountsPage, &AccountsPage::onAccountsFailed);
    connect(m_accountsService, &AccountsService::accountCreated,
    this, [this](const Models::Account&){
        onRequestAccountsList();
    });

    connect(m_transactionsService, &TransactionsService::transactionsUpdated,
            m_transactionsPage, &TransactionsPage::onTransactionsUpdated);
    connect(m_transactionsService, &TransactionsService::transactionsFailed,
            m_transactionsPage, &TransactionsPage::onTransactionsFailed);
    connect(m_transactionsService, &TransactionsService::transactionCreated,
            m_transactionsPage, &TransactionsPage::onTransactionCreated);
}

//==============================================================================================================================================================//

void MainWindow::showPage(PageIndex index)
{
    m_stackedWidget->setCurrentIndex(static_cast<int>(index));
}

void MainWindow::routeMessage(const QByteArray &msg)
{
    qDebug() << msg; //DEBUG

    {
        QJsonDocument doc = QJsonDocument::fromJson(msg);
        if (!doc.isObject()) return;

        QJsonObject obj = doc.object();
        QString type = obj.value("type").toString();
        if (type == "login" || type == "register")
        {
            m_authService->handleMessage(msg);
        }
        else if (type.startsWith("account"))
        {
            m_accountsService->handleMessage(msg);
        }
        else if (type.startsWith("transaction"))
        {
            m_transactionsService->handleMessage(msg);
        }
        else
        {
            qDebug() << "Unknown message type" << type;
        }
    }
}

//==============================================================================================================================================================//

void MainWindow::onRequestConnect(QString host, quint16 port)
{
    m_client->connect(host, port);
}

void MainWindow::onRequestLogin(const QString &username, const QString &password)
{
    auto data = m_authService->createLoginRequest(username, password);
    qDebug() << data; //DEBUG
    m_client->send(data);
}

void MainWindow::onRequestRegistration(const RegData &regData)
{
    auto data = m_authService->createRegistrationRequest(regData);
    qDebug() << data; //DEBUG
    m_client->send(data);
}

void MainWindow::onRequestLogout()
{
    if (m_client) {
        m_client->disconnect();
    }
    m_connectPage->reset();
    showPage(PageConnect);
}
void MainWindow::onRequestAccountsList()
{
    AuthDelegate authenticate = [this](QJsonObject &request) {
        m_authService->setAuthentificationData(request);
    };

    std::pair<QString, QString> sessionData = m_authService->getSessionData();
    if (!sessionData.first.isEmpty() && !sessionData.second.isEmpty())
        m_client->send(m_accountsService->createAccListRequest(authenticate));
    else
        m_accountsPage->onAccountsFailed(tr("Нет сессии — войдите заново"));
}

void MainWindow::onRequestTransactionsList()
{
    AuthDelegate authenticate = [this](QJsonObject &request) {
        m_authService->setAuthentificationData(request);
    };

    std::pair<QString, QString> sessionData = m_authService->getSessionData();
    if (!sessionData.first.isEmpty() && !sessionData.second.isEmpty())
        m_client->send(m_transactionsService->createTrListRequest(authenticate));
    else
        m_transactionsPage->onTransactionsFailed(tr("Нет сессии — войдите заново"));
}

void MainWindow::onRequestCreateAccount(Enums::Currency curr)
{
    AuthDelegate authenticate = [this](QJsonObject &request) {
        m_authService->setAuthentificationData(request);
    };

    std::pair<QString, QString> sessionData = m_authService->getSessionData();
    if (!sessionData.first.isEmpty() && !sessionData.second.isEmpty())
        m_client->send(m_accountsService->createAccCreateRequest(authenticate, curr));
    else
        m_accountsPage->onAccountsFailed(tr("Нет сессии — войдите заново"));
}

void MainWindow::onRequestCreateTransaction(const QString &fromAccountId,
                                            const QString &to,
                                            const QString &amount,
                                            const Enums::Currency &currency,
                                            const QString &description)
{
    AuthDelegate authenticate = [this](QJsonObject &request) {
        m_authService->setAuthentificationData(request);
    };

    std::pair<QString, QString> sessionData = m_authService->getSessionData();
    if (!sessionData.first.isEmpty() && !sessionData.second.isEmpty())
        m_client->send(m_transactionsService->createTransferRequest(authenticate, fromAccountId, to, amount, currency, description));
    else
        m_transactionsPage->onTransactionsFailed(tr("Нет сессии — войдите заново"));
}

void MainWindow::onRequestTestCredit(const QString &accountId, const QString &amount)
{
    AuthDelegate authenticate = [this](QJsonObject &request) {
        m_authService->setAuthentificationData(request);
    };

    std::pair<QString, QString> sessionData = m_authService->getSessionData();
    if (!sessionData.first.isEmpty() && !sessionData.second.isEmpty())
    {
        bool isCorrect = false;
        const double val = amount.toDouble(&isCorrect);
        if (isCorrect && val > 0.0)
        {
            const QString from = QStringLiteral("SYSTEM");
            const QString description = QStringLiteral("Test credit");
            m_client->send(m_transactionsService->createTransferRequest(authenticate, from, accountId, amount, Enums::Currency::BYN, description));
        }
        else
            m_accountsPage->onAccountsFailed(tr("Некорректная сумма для тестового начисления"));
    }
    else
        m_accountsPage->onAccountsFailed(tr("Нет сессии — войдите заново"));
}
