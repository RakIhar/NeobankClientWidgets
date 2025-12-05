#ifndef TRANSACTIONSPAGE_H
#define TRANSACTIONSPAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QListWidget;
class QPushButton;
class QLabel;
QT_END_NAMESPACE

class SocketHandler;

class TransactionsPage : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionsPage(SocketHandler *client, QWidget *parent = nullptr);
    void refreshTransactions();

signals:
    void backToDashboard();

private slots:
    void onBackClicked();
    void onRefreshClicked();

private:
    SocketHandler *m_client;
    QListWidget *m_transactionsList;
    QPushButton *m_backButton;
    QPushButton *m_refreshButton;
    QLabel *m_statusLabel;
};

#endif // TRANSACTIONSPAGE_H

