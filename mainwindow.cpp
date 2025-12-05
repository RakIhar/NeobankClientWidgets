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
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QJsonObject>

//UI сигнал/вызов MainWindow
//MainWindow вызов Service для получения json из запроса от UI
//MainWindow вызов SocketHandler для отправки json

//SocketHandler сигнал MainWindow
//MainWindow вызов Service для обработки json
//Service сигнал UI/MainWindow

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_client(std::make_unique<SocketHandler>(this))
    , m_stackedWidget(nullptr)
    , m_connectPage(nullptr)
    , m_loginPage(nullptr)
    , m_dashboardPage(nullptr)
    , m_accountsPage(nullptr)
    , m_transactionsPage(nullptr)
    , m_registrationPage(nullptr)
    , m_authService(nullptr)
{
    ui->setupUi(this);
    setWindowTitle(tr("NeoBank Client"));

    setupPages();
    setupPageConnections();
    connect(m_client.get(), &SocketHandler::messageReceived, this, [this](const QByteArray &msg){
        qDebug() << msg; //DEBUG
        this->m_authService->handleMessage(msg);
        //остальные сервисы
    });
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

    m_connectPage = new ConnectPage(this);
    m_loginPage = new LoginPage(this);
    m_dashboardPage = new DashboardPage(this);
    m_accountsPage = new AccountsPage(m_client.get(), this);
    m_registrationPage = new RegistrationPage(this);
    m_transactionsPage = new TransactionsPage(m_client.get(), this);

    m_authService = new AuthService(this);

    m_stackedWidget->addWidget(m_connectPage);
    m_stackedWidget->addWidget(m_loginPage);
    m_stackedWidget->addWidget(m_dashboardPage);
    m_stackedWidget->addWidget(m_accountsPage);
    m_stackedWidget->addWidget(m_transactionsPage);
    m_stackedWidget->addWidget(m_registrationPage);
}

void MainWindow::setupPageConnections()
{

    connect(m_dashboardPage, &DashboardPage::showAccounts,
            this, &MainWindow::onDashboardShowAccounts);
    connect(m_dashboardPage, &DashboardPage::showTransactions,
            this, &MainWindow::onDashboardShowTransactions);
    connect(m_dashboardPage, &DashboardPage::logout,
            this, &MainWindow::onDashboardLogout);
    connect(m_accountsPage, &AccountsPage::backToDashboard,
            this, &MainWindow::onAccountsBack);
    connect(m_transactionsPage, &TransactionsPage::backToDashboard,
            this, &MainWindow::onTransactionsBack);

    setupConnection();
    setupLoginRegistration();
}

void MainWindow::showPage(PageIndex index)
{
    m_stackedWidget->setCurrentIndex(static_cast<int>(index));
}

/*
LOGIN PAGE:
signals:
    void loginRequested(const QString &username, const QString &password);
    void registrationRequested();
public slots:
    // void onLoginSuccess();
    void onLoginError(const QString &reason); //обновить интерфейс
*/

/*
REGISTRATION PAGE:
signals:
    void loginPageRequested();
    void registrationRequested(const RegData &regData);

public slots:
    void onRegistrationError(const QString &error);
    void onRegistrationSuccess();

*/
/*
AUTH SERVICE
signals:
    void loginSuccess();
    void loginFailed(const QString &reason);
    void registerSuccess();
    void registerFailed(const QString &reason);

public slots:
    void handleMessage(const QJsonObject &msg);
*/
void MainWindow::setupLoginRegistration()
{
    //настройка loginpage, registrationpage, authservice
    connect(m_loginPage, &LoginPage::loginRequested,
            this, &MainWindow::onLoginRequested);
    connect(m_loginPage, &LoginPage::registrationPageRequested, this, [this](){
        showPage(PageRegistration);
    });
    connect(m_authService, &AuthService::loginSuccess,
            this, &MainWindow::onLoginSuccess);
    connect(m_authService, &AuthService::loginFailed,
            m_loginPage, &LoginPage::onLoginError);

    connect(m_registrationPage, &RegistrationPage::loginPageRequested, this, [this](){
        showPage(PageLogin);
    });
    connect(m_registrationPage, &RegistrationPage::registrationRequested,
            this, &MainWindow::onRegistrationRequested);
    connect(m_authService, &AuthService::registerSuccess,
            m_registrationPage, &RegistrationPage::onRegistrationSuccess);
    connect(m_authService, &AuthService::registerFailed,
            m_registrationPage, &RegistrationPage::onRegistrationError);
}

void MainWindow::setupConnection()
{
    connect(m_connectPage, &ConnectPage::connectRequested,
            this, &MainWindow::onConnectRequested);
    connect(m_client.get(), &SocketHandler::connected, this, [this](){
        showPage(PageLogin);
    });
    connect(m_client.get(), &SocketHandler::errorOccurred,
            m_connectPage, &ConnectPage::onSocketError);
}

void MainWindow::onConnectRequested(QString host, quint16 port)
{
    m_client->connectToServer(host, port);
}

void MainWindow::onLoginRequested(const QString &username, const QString &password)
{
    auto data = m_authService->createLoginRequest(username, password);
    qDebug() << data; //DEBUG
    m_client->sendData(data);
}

void MainWindow::onRegistrationRequested(const RegData &regData)
{
    auto data = m_authService->createRegistrationRequest(regData);
    qDebug() << data; //DEBUG
    m_client->sendData(data);
}

void MainWindow::onLoginSuccess()
{
    //Доп логика: запросы информации об аккаунте, поэтому покуда не в лямбде
    showPage(PageDashboard);
}


void MainWindow::onDashboardShowAccounts()
{
    m_accountsPage->refreshAccounts();
    showPage(PageAccounts);
}

void MainWindow::onDashboardShowTransactions()
{
    m_transactionsPage->refreshTransactions();
    showPage(PageTransactions);
}

void MainWindow::onDashboardLogout()
{
    if (m_client) {
        m_client->disconnectFromServer();
    }
    showPage(PageLogin);
}

void MainWindow::onAccountsBack()
{
    showPage(PageDashboard);
}

void MainWindow::onTransactionsBack()
{
    showPage(PageDashboard);
}
