/********************************************************************************
** Form generated from reading UI file 'accountspage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTSPAGE_H
#define UI_ACCOUNTSPAGE_H

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

class Ui_AccountsPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QGroupBox *accountsGroup;
    QVBoxLayout *groupLayout;
    QListWidget *accountsList;
    QHBoxLayout *buttonsLayout;
    QPushButton *backButton;
    QSpacerItem *hSpacer;
    QPushButton *createButton;
    QPushButton *testCreditButton;
    QPushButton *refreshButton;
    QLabel *statusLabel;

    void setupUi(QWidget *AccountsPage)
    {
        if (AccountsPage->objectName().isEmpty())
            AccountsPage->setObjectName("AccountsPage");
        AccountsPage->resize(900, 600);
        verticalLayout = new QVBoxLayout(AccountsPage);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(AccountsPage);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(30);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        accountsGroup = new QGroupBox(AccountsPage);
        accountsGroup->setObjectName("accountsGroup");
        groupLayout = new QVBoxLayout(accountsGroup);
        groupLayout->setObjectName("groupLayout");
        accountsList = new QListWidget(accountsGroup);
        accountsList->setObjectName("accountsList");

        groupLayout->addWidget(accountsList);


        verticalLayout->addWidget(accountsGroup);

        buttonsLayout = new QHBoxLayout();
        buttonsLayout->setObjectName("buttonsLayout");
        backButton = new QPushButton(AccountsPage);
        backButton->setObjectName("backButton");
        QFont font1;
        font1.setBold(true);
        backButton->setFont(font1);

        buttonsLayout->addWidget(backButton);

        hSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonsLayout->addItem(hSpacer);

        createButton = new QPushButton(AccountsPage);
        createButton->setObjectName("createButton");
        createButton->setFont(font1);

        buttonsLayout->addWidget(createButton);

        testCreditButton = new QPushButton(AccountsPage);
        testCreditButton->setObjectName("testCreditButton");
        testCreditButton->setFont(font1);

        buttonsLayout->addWidget(testCreditButton);

        refreshButton = new QPushButton(AccountsPage);
        refreshButton->setObjectName("refreshButton");
        refreshButton->setFont(font1);

        buttonsLayout->addWidget(refreshButton);


        verticalLayout->addLayout(buttonsLayout);

        statusLabel = new QLabel(AccountsPage);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(statusLabel);


        retranslateUi(AccountsPage);

        QMetaObject::connectSlotsByName(AccountsPage);
    } // setupUi

    void retranslateUi(QWidget *AccountsPage)
    {
        titleLabel->setText(QCoreApplication::translate("AccountsPage", "\320\220\320\272\320\272\320\260\321\203\320\275\321\202\321\213", nullptr));
        accountsGroup->setTitle(QCoreApplication::translate("AccountsPage", "[ \320\241\320\277\320\270\321\201\320\276\320\272 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\276\320\262 ]", nullptr));
        backButton->setText(QCoreApplication::translate("AccountsPage", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        createButton->setText(QCoreApplication::translate("AccountsPage", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\201\321\207\321\221\321\202", nullptr));
        testCreditButton->setText(QCoreApplication::translate("AccountsPage", "\320\242\320\265\321\201\321\202\320\276\320\262\320\276\320\265 \320\275\320\260\321\207\320\270\321\201\320\273\320\265\320\275\320\270\320\265", nullptr));
        refreshButton->setText(QCoreApplication::translate("AccountsPage", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        statusLabel->setText(QString());
        (void)AccountsPage;
    } // retranslateUi

};

namespace Ui {
    class AccountsPage: public Ui_AccountsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTSPAGE_H
