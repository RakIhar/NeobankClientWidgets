#ifndef TRANSFERDIALOG_H
#define TRANSFERDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui { class TransferDialog; }

struct TransferData {
    QString fromAccount;
    QString toAccount;
    QString amount;
    QString currency;
    QString description;
};

class TransferDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TransferDialog(QWidget *parent = nullptr);
    ~TransferDialog();

    void setFromAccount(const QString &from);
    TransferData resultData() const;

private:
    Ui::TransferDialog *ui;
    TransferData m_data;
};

#endif // TRANSFERDIALOG_H
