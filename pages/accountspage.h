#ifndef ACCOUNTSPAGE_H
#define ACCOUNTSPAGE_H

#include "ui_accountspage.h"
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include "../services/accountsservice.h"
// #include "transferdialog.h"

class AccountsPage : public QWidget
{
    Q_OBJECT
public:
    explicit AccountsPage(QWidget *parent = nullptr);
    void refreshAccounts();
    void showLoading(const QString &message = QString());

signals:
    void pr_dashboard();
    void r_accounts();
    ///CHECK
    void r_transferRequested(const QString &fromAccountId,
                             const QString &to,
                             const QString &amount,
                             const Enums::Currency &currency,
                             const QString &description);
    void r_createAccount(Enums::Currency curr);
    void r_testCreditRequested(const QString &accountId, const QString &amount);
    ///
public slots:
    void onAccountsUpdated(const QList<AccountInfo> &accounts);
    void onAccountsFailed(const QString &reason);

//===========================================================//

private:
    void setupConnections();
    Ui::AccountsPage *ui;
    QList<AccountInfo> m_accounts; //CHECK
};

#endif // ACCOUNTSPAGE_H

