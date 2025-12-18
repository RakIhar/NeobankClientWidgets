#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "network/socketwrapper.h"
#include "pages/accountspage.h"
#include "pages/connectpage.h"
#include "pages/dashboardpage.h"
#include "pages/loginpage.h"
#include "pages/registrationpage.h"
#include "pages/transactionspage.h"
#include "services/authservice.h"
#include "services/transactionsservice.h"
#include "constants.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<SocketWrapper> m_client;
    QStackedWidget *m_stackedWidget;

    //=====PAGES=====//
    ConnectPage *m_connectPage;
    LoginPage *m_loginPage;
    RegistrationPage *m_registrationPage;
    DashboardPage *m_dashboardPage;
    AccountsPage *m_accountsPage;
    TransactionsPage *m_transactionsPage;

    enum PageIndex {
        PageConnect = 0,
        PageLogin = 1,
        PageDashboard = 2,
        PageAccounts = 3,
        PageTransactions = 4,
        PageRegistration = 5
    };

    //====SERVICES====//
    AuthService *m_authService;
    AccountsService *m_accountsService;
    TransactionsService *m_transactionsService;


    //======CTR======//
    void setupPagesServices();
    void setupPageSwapConnections();
    void setupRequestConnections();
    void setupConnectionsFromServicesToPages();

    //=====OTHER=====//
    void showPage(PageIndex index);
    void routeMessage(const QByteArray &msg);

private slots:
    //===REQUESTS===//
    void onRequestConnect(QString host, quint16 port);
    void onRequestLogin(const QString &username, const QString &password);
    void onRequestRegistration(const RegData &regData);
    void onRequestLogout();
    void onRequestAccountsList();
    void onRequestTransactionsList();
    void onRequestCreateTransaction(const QString &fromAccountId,
                                    const QString &to,
                                    const QString &amount,
                                    const Enums::Currency &currency,
                                    const QString &description);
    void onRequestCreateAccount(const Enums::Currency curr);
    void onRequestTestCredit(const QString &accountId, const QString &amount);
private:

};
#endif // MAINWINDOW_H
