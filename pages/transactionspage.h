#ifndef TRANSACTIONSPAGE_H
#define TRANSACTIONSPAGE_H

#include "ui_transactionspage.h"
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include "../models/transaction.h"

class TransactionsPage : public QWidget
{
    Q_OBJECT
public:
    explicit TransactionsPage(QWidget *parent = nullptr);
    void refreshTransactions();
    void showLoading(const QString &message = QString());

signals:
    void pr_dashboard();
    void r_transactions(const int limit = 50, const int page = 0);

public slots:
    void onTransactionsUpdated(const QList<Models::Transaction> &transactions);
    void onTransactionsFailed(const QString &reason);
    void onTransactionCreated(const Models::Transaction &transaction);

private:
    void setupConnections();
    Ui::TransactionsPage *ui;
};

#endif // TRANSACTIONSPAGE_H

