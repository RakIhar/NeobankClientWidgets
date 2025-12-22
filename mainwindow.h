#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "network/socketwrapper.h"
#include "services/authservice.h"
#include "services/transactionsservice.h"
#include "services/accountsservice.h"
#include "pages/connectpage.h"
#include "pages/loginpage.h"
#include "pages/dashboardpage.h"
#include "pages/accountspage.h"
#include "pages/transactionspage.h"
#include "pages/registrationpage.h"
#include "pages/transferpage.h"

struct Pages
{
    ConnectPage      *connectPage;
    LoginPage        *loginPage;
    DashboardPage    *dashboardPage;
    AccountsPage     *accountsPage;
    RegistrationPage *registrationPage;
    TransactionsPage *transactionsPage;
    TransferPage     *transferPage;
};

enum PageIndex {
    PageConnect      = 0,
    PageLogin        = 1,
    PageDashboard    = 2,
    PageAccounts     = 3,
    PageTransactions = 4,
    PageRegistration = 5,
    PageTransfer     = 6
};

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
    Pages m_pages;

    AuthService         *m_authService = nullptr;
    AccountsService     *m_accountsService = nullptr;
    TransactionsService *m_transactionsService = nullptr;
    

    void setupPages();
    void setupServices();
    void setupSwaps();
    void routeMessage(const QByteArray &msg);
    void showPage(PageIndex index) { m_stackedWidget->setCurrentIndex(static_cast<int>(index)); }
};
#endif // MAINWINDOW_H
