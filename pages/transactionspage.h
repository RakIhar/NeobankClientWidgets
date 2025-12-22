#ifndef TRANSACTIONSPAGE_H
#define TRANSACTIONSPAGE_H

#include "ui_transactionspage.h"
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include "../models/transaction.h"
#include "../services/transactionsservice.h"

class TransactionsPage : public QWidget
{
    Q_OBJECT
public:
    explicit TransactionsPage(TransactionsService *trService, QWidget *parent = nullptr);
    ~TransactionsPage();
    void refreshTransactions();
    void showLoading(const QString &message = QString());

signals:
    void pr_dashboard();

private slots:
    void onTransactionsUpdated(const QList<Models::Transaction> &transactions);
    void onTransactionsFailed(const QString &reason);
    void onTransactionCreated(const Models::Transaction &transaction);
    void onTransactionsCount(int total, int page, int limit);

private:
    void setupConnections();
    TransactionsService *m_trService;
    Ui::TransactionsPage *ui;
};

#endif // TRANSACTIONSPAGE_H

