#ifndef ACCOUNTSPAGE_H
#define ACCOUNTSPAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QListWidget;
class QPushButton;
class QLabel;
QT_END_NAMESPACE

class SocketHandler;

class AccountsPage : public QWidget
{
    Q_OBJECT

public:
    explicit AccountsPage(SocketHandler *client, QWidget *parent = nullptr);
    void refreshAccounts();

signals:
    void backToDashboard();

private slots:
    void onBackClicked();
    void onRefreshClicked();

private:
    SocketHandler *m_client;
    QListWidget *m_accountsList;
    QPushButton *m_backButton;
    QPushButton *m_refreshButton;
    QLabel *m_statusLabel;
};

#endif // ACCOUNTSPAGE_H

