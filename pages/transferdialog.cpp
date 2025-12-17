#include "transferdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDoubleValidator>
#include <QMessageBox>
///CHECKALL
TransferDialog::TransferDialog(QWidget *parent)
    : QDialog(parent), ui(nullptr)
{
    setWindowTitle(tr("Перевод средств"));
    setModal(true);

    auto *layout = new QVBoxLayout(this);
    auto *fromLabel = new QLabel(tr("Отправитель:"), this);
    layout->addWidget(fromLabel);
    auto *fromEdit = new QLineEdit(this);
    fromEdit->setReadOnly(true);
    fromEdit->setObjectName("fromEdit");
    layout->addWidget(fromEdit);

    auto *toLabel = new QLabel(tr("Кому (ID/IBAN):"), this);
    layout->addWidget(toLabel);
    auto *toEdit = new QLineEdit(this);
    toEdit->setObjectName("toEdit");
    layout->addWidget(toEdit);

    auto *amountLabel = new QLabel(tr("Сумма:"), this);
    layout->addWidget(amountLabel);
    auto *amountEdit = new QLineEdit(this);
    amountEdit->setObjectName("amountEdit");
    layout->addWidget(amountEdit);

    auto *currencyLabel = new QLabel(tr("Валюта:"), this);
    layout->addWidget(currencyLabel);
    auto *currencyBox = new QComboBox(this);
    currencyBox->addItems({"₽", "USD", "EUR"});
    currencyBox->setObjectName("currencyBox");
    layout->addWidget(currencyBox);

    auto *descLabel = new QLabel(tr("Комментарий:"), this);
    layout->addWidget(descLabel);
    auto *descEdit = new QLineEdit(this);
    descEdit->setObjectName("descEdit");
    layout->addWidget(descEdit);

    auto *buttons = new QHBoxLayout();
    auto *ok = new QPushButton(tr("Отправить"), this);
    auto *cancel = new QPushButton(tr("Отмена"), this);
    ok->setObjectName("okButton");
    ok->setEnabled(false);
    buttons->addWidget(ok);
    buttons->addWidget(cancel);
    layout->addLayout(buttons);

    // Validator for numeric amount
    amountEdit->setValidator(new QDoubleValidator(0.01, 1e12, 2, this));

    auto updateOk = [this]() {
        QLineEdit *to = findChild<QLineEdit *>("toEdit");
        QLineEdit *amount = findChild<QLineEdit *>("amountEdit");
        QPushButton *okBtn = findChild<QPushButton *>("okButton");
        bool enabled = false;
        if (to && amount && okBtn) {
            const QString toText = to->text().trimmed();
            const QString amountText = amount->text().trimmed();
            bool okNum = false;
            const double val = amountText.toDouble(&okNum);
            enabled = !toText.isEmpty() && okNum && val > 0.0;
            okBtn->setEnabled(enabled);
        }
    };

    connect(toEdit, &QLineEdit::textChanged, this, updateOk);
    connect(amountEdit, &QLineEdit::textChanged, this, updateOk);

    connect(ok, &QPushButton::clicked, this, [this]{
        QLineEdit *to = findChild<QLineEdit *>("toEdit");
        QLineEdit *amount = findChild<QLineEdit *>("amountEdit");
        QComboBox *currency = findChild<QComboBox *>("currencyBox");
        QLineEdit *desc = findChild<QLineEdit *>("descEdit");
        if (!to || !amount || !currency || !desc) {
            QMessageBox::warning(this, tr("Ошибка"), tr("Поля отсутствуют"));
            return;
        }
        bool okNum = false;
        const double val = amount->text().toDouble(&okNum);
        if (!okNum || val <= 0.0) {
            QMessageBox::warning(this, tr("Неверная сумма"), tr("Введите корректную положительную сумму"));
            return;
        }
        m_data.toAccount = to->text();
        m_data.amount = amount->text();
        m_data.currency = currency->currentText();
        m_data.description = desc->text();
        accept();
    });

    connect(cancel, &QPushButton::clicked, this, [this]{ reject(); });
}

TransferDialog::~TransferDialog() = default;

void TransferDialog::setFromAccount(const QString &from)
{
    m_data.fromAccount = from;
    QLineEdit *fromEdit = findChild<QLineEdit *>("fromEdit");
    if (fromEdit) fromEdit->setText(from);
}

TransferData TransferDialog::resultData() const
{
    TransferData d;
    d.fromAccount = m_data.fromAccount;
    d.toAccount = m_data.toAccount;
    d.amount = m_data.amount;
    d.currency = m_data.currency;
    d.description = m_data.description;
    return d;
}
