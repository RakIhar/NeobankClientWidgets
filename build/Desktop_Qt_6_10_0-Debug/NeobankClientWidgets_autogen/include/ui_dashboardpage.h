/********************************************************************************
** Form generated from reading UI file 'dashboardpage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARDPAGE_H
#define UI_DASHBOARDPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DashboardPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *welcomeLabel;
    QGroupBox *balanceGroup;
    QVBoxLayout *balanceLayout;
    QLabel *balanceLabel;
    QGroupBox *actionsGroup;
    QGridLayout *actionsLayout;
    QPushButton *accountsButton;
    QPushButton *transactionsButton;
    QPushButton *logoutButton;

    void setupUi(QWidget *DashboardPage)
    {
        if (DashboardPage->objectName().isEmpty())
            DashboardPage->setObjectName("DashboardPage");
        DashboardPage->resize(900, 700);
        verticalLayout = new QVBoxLayout(DashboardPage);
        verticalLayout->setObjectName("verticalLayout");
        welcomeLabel = new QLabel(DashboardPage);
        welcomeLabel->setObjectName("welcomeLabel");
        QFont font;
        font.setPointSize(30);
        welcomeLabel->setFont(font);
        welcomeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(welcomeLabel);

        balanceGroup = new QGroupBox(DashboardPage);
        balanceGroup->setObjectName("balanceGroup");
        QFont font1;
        font1.setBold(true);
        balanceGroup->setFont(font1);
        balanceLayout = new QVBoxLayout(balanceGroup);
        balanceLayout->setObjectName("balanceLayout");
        balanceLabel = new QLabel(balanceGroup);
        balanceLabel->setObjectName("balanceLabel");
        balanceLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        balanceLayout->addWidget(balanceLabel);


        verticalLayout->addWidget(balanceGroup);

        actionsGroup = new QGroupBox(DashboardPage);
        actionsGroup->setObjectName("actionsGroup");
        actionsLayout = new QGridLayout(actionsGroup);
        actionsLayout->setObjectName("actionsLayout");
        accountsButton = new QPushButton(actionsGroup);
        accountsButton->setObjectName("accountsButton");
        accountsButton->setFont(font1);

        actionsLayout->addWidget(accountsButton, 0, 0, 1, 1);

        transactionsButton = new QPushButton(actionsGroup);
        transactionsButton->setObjectName("transactionsButton");
        transactionsButton->setFont(font1);

        actionsLayout->addWidget(transactionsButton, 0, 1, 1, 1);


        verticalLayout->addWidget(actionsGroup);

        logoutButton = new QPushButton(DashboardPage);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setFont(font1);

        verticalLayout->addWidget(logoutButton);


        retranslateUi(DashboardPage);

        QMetaObject::connectSlotsByName(DashboardPage);
    } // setupUi

    void retranslateUi(QWidget *DashboardPage)
    {
        welcomeLabel->setText(QCoreApplication::translate("DashboardPage", "\320\237\320\260\320\275\320\265\320\273\321\214", nullptr));
        balanceGroup->setTitle(QCoreApplication::translate("DashboardPage", "\320\236\320\261\321\211\320\270\320\271 \320\261\320\260\320\273\320\260\320\275\321\201", nullptr));
        balanceLabel->setText(QCoreApplication::translate("DashboardPage", "0.00 \342\202\275", nullptr));
        actionsGroup->setTitle(QCoreApplication::translate("DashboardPage", "[ \320\221\321\213\321\201\321\202\321\200\321\213\320\265 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\321\217 ]", nullptr));
        accountsButton->setText(QCoreApplication::translate("DashboardPage", "\320\241\321\207\320\265\321\202\320\260", nullptr));
        transactionsButton->setText(QCoreApplication::translate("DashboardPage", "\320\242\321\200\320\260\320\275\320\267\320\260\320\272\321\206\320\270\320\270", nullptr));
        logoutButton->setText(QCoreApplication::translate("DashboardPage", "\320\222\321\213\320\271\321\202\320\270", nullptr));
        (void)DashboardPage;
    } // retranslateUi

};

namespace Ui {
    class DashboardPage: public Ui_DashboardPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARDPAGE_H
