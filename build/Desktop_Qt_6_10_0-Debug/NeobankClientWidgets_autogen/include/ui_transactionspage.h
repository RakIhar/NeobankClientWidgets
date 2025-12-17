/********************************************************************************
** Form generated from reading UI file 'transactionspage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSACTIONSPAGE_H
#define UI_TRANSACTIONSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TransactionsPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QGroupBox *transactionsGroup;
    QVBoxLayout *groupLayout;
    QListWidget *transactionsList;
    QHBoxLayout *buttonsLayout;
    QPushButton *backButton;
    QSpacerItem *hSpacer;
    QPushButton *refreshButton;
    QLabel *statusLabel;

    void setupUi(QWidget *TransactionsPage)
    {
        if (TransactionsPage->objectName().isEmpty())
            TransactionsPage->setObjectName("TransactionsPage");
        TransactionsPage->resize(900, 700);
        verticalLayout = new QVBoxLayout(TransactionsPage);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(TransactionsPage);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Ubuntu")});
        font.setPointSize(30);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        transactionsGroup = new QGroupBox(TransactionsPage);
        transactionsGroup->setObjectName("transactionsGroup");
        groupLayout = new QVBoxLayout(transactionsGroup);
        groupLayout->setObjectName("groupLayout");
        transactionsList = new QListWidget(transactionsGroup);
        transactionsList->setObjectName("transactionsList");

        groupLayout->addWidget(transactionsList);


        verticalLayout->addWidget(transactionsGroup);

        buttonsLayout = new QHBoxLayout();
        buttonsLayout->setObjectName("buttonsLayout");
        backButton = new QPushButton(TransactionsPage);
        backButton->setObjectName("backButton");
        QFont font1;
        font1.setBold(true);
        backButton->setFont(font1);

        buttonsLayout->addWidget(backButton);

        hSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonsLayout->addItem(hSpacer);

        refreshButton = new QPushButton(TransactionsPage);
        refreshButton->setObjectName("refreshButton");
        refreshButton->setFont(font1);

        buttonsLayout->addWidget(refreshButton);


        verticalLayout->addLayout(buttonsLayout);

        statusLabel = new QLabel(TransactionsPage);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);


        retranslateUi(TransactionsPage);

        QMetaObject::connectSlotsByName(TransactionsPage);
    } // setupUi

    void retranslateUi(QWidget *TransactionsPage)
    {
        titleLabel->setText(QCoreApplication::translate("TransactionsPage", "\320\242\321\200\320\260\320\275\320\267\320\260\320\272\321\206\320\270\320\270", nullptr));
        transactionsGroup->setTitle(QCoreApplication::translate("TransactionsPage", "[ \320\241\320\277\320\270\321\201\320\276\320\272 \321\202\321\200\320\260\320\275\320\267\320\260\320\272\321\206\320\270\320\271 ]", nullptr));
        backButton->setText(QCoreApplication::translate("TransactionsPage", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        refreshButton->setText(QCoreApplication::translate("TransactionsPage", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        (void)TransactionsPage;
    } // retranslateUi

};

namespace Ui {
    class TransactionsPage: public Ui_TransactionsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSACTIONSPAGE_H
