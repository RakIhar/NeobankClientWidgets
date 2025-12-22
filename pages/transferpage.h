#ifndef TRANSFERDIALOG_H
#define TRANSFERDIALOG_H

#include <QDialog>
#include <QString>
#include "../models/transaction.h"
#include "../models/account.h"
#include "../services/transactionsservice.h"

#include "ui_transferpage.h"

namespace Ui { class TransferDialog; }

class TransferPage : public QDialog
{
    Q_OBJECT
public:
    explicit TransferPage(TransactionsService *trService,
                          QWidget *parent = nullptr);
    ~TransferPage();
    void reset(const Models::Account &from);

signals:
    void pr_back();

private slots:
    void onBeforeTransferInfo(const BeforeTransferInfo& info);

private:
    void setupConnections();
    Ui::TransferDialog *ui;
    TransactionsService *m_trService;
    TransferData m_data;
    void setInfoText();
    void setInfoText(const BeforeTransferInfo &beforeTransferInfo);
};

#endif // TRANSFERDIALOG_H
