#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class SocketHandler;
class QStackedWidget;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class ConnectPage;
class LoginPage;
class DashboardPage;
class AccountsPage;
class TransactionsPage;
class RegistrationPage;
class AuthService;
class RegData;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<SocketHandler> m_client;
    QStackedWidget *m_stackedWidget;

    ConnectPage *m_connectPage;
    LoginPage *m_loginPage;
    RegistrationPage *m_registrationPage;
    DashboardPage *m_dashboardPage;
    AccountsPage *m_accountsPage;
    TransactionsPage *m_transactionsPage;

    AuthService *m_authService;

    enum PageIndex {
        PageConnect = 0,
        PageLogin = 1,
        PageDashboard = 2,
        PageAccounts = 3,
        PageTransactions = 4,
        PageRegistration = 5
    };

    void setupPages();
    void setupPageConnections();
    void showPage(PageIndex index);

    void setupLoginRegistration();
    void setupConnection();


private slots:
    void onConnectRequested(QString host, quint16 port);

    void onLoginRequested(const QString &username, const QString &password); //LoginPage
    void onRegistrationRequested(const RegData &regData); //PageLogin, ConnectPage
    // void onRegistrationRequested(...); //RegistrationPage, недописано
    void onLoginSuccess(); //AuthService
    // void onLoginPageRequested(); //RegistrationPage, излишне, можно лямбду
    //onLoginError обрабатывает LoginPage
    //onRegistrationSuccess, onRegistrationError обрабатывает RegistrationPage

    // void onConnectPageConnected();
    // void onLoginPageSuccess();
    // void onRegistration();
    // void onRegistrationBack();
    void onDashboardShowAccounts();
    void onDashboardShowTransactions();
    void onDashboardLogout();
    void onAccountsBack();
    void onTransactionsBack();
};
#endif // MAINWINDOW_H
