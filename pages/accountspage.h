#ifndef ACCOUNTSPAGE_H
#define ACCOUNTSPAGE_H

#include "ui_accountspage.h"
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include "../models/account.h"
#include "../services/accountsservice.h"
#include "../services/transactionsservice.h"

class AccountsPage : public QWidget
{
    Q_OBJECT
public:
    explicit AccountsPage(AccountsService *accService, TransactionsService* trService, QWidget *parent = nullptr);
    ~AccountsPage();
    void refreshAccounts();
    void showLoading(const QString &message = QString());

signals:
    void pr_dashboard();
    void pr_transfer(Models::Account fromAcc);

public slots:
    void onAccountsUpdated(const QList<Models::Account> &accounts);
    void onAccountsFailed(const QString &reason);

private slots:
    void onTestCredit();

private:
    void setupConnections();
    AccountsService *m_accService;
    TransactionsService *m_trService;
    Ui::AccountsPage *ui;
    QList<Models::Account> m_accounts;
};

#endif // ACCOUNTSPAGE_H
