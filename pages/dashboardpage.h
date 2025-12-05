#ifndef DASHBOARDPAGE_H
#define DASHBOARDPAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QVBoxLayout;
QT_END_NAMESPACE

class DashboardPage : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardPage(QWidget *parent = nullptr);

signals:
    void showAccounts();
    void showTransactions();
    void logout();

private slots:
    void onAccountsClicked();
    void onTransactionsClicked();
    void onLogoutClicked();

private:
    QLabel *m_welcomeLabel;
    QLabel *m_balanceLabel;
    QPushButton *m_accountsButton;
    QPushButton *m_transactionsButton;
    QPushButton *m_logoutButton;
};

#endif // DASHBOARDPAGE_H

