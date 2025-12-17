/********************************************************************************
** Form generated from reading UI file 'loginpage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINPAGE_H
#define UI_LOGINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginPage
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *spacerTop;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QGroupBox *loginGroup;
    QFormLayout *formLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QLabel *statusLabel;
    QSpacerItem *spacerBottom;

    void setupUi(QWidget *LoginPage)
    {
        if (LoginPage->objectName().isEmpty())
            LoginPage->setObjectName("LoginPage");
        LoginPage->resize(800, 600);
        QFont font;
        font.setFamilies({QString::fromUtf8("Ubuntu")});
        LoginPage->setFont(font);
        verticalLayout = new QVBoxLayout(LoginPage);
        verticalLayout->setObjectName("verticalLayout");
        spacerTop = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(spacerTop);

        titleLabel = new QLabel(LoginPage);
        titleLabel->setObjectName("titleLabel");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Ubuntu")});
        font1.setPointSize(30);
        font1.setBold(false);
        titleLabel->setFont(font1);
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        subtitleLabel = new QLabel(LoginPage);
        subtitleLabel->setObjectName("subtitleLabel");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Ubuntu")});
        font2.setItalic(true);
        subtitleLabel->setFont(font2);
        subtitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(subtitleLabel);

        loginGroup = new QGroupBox(LoginPage);
        loginGroup->setObjectName("loginGroup");
        loginGroup->setFont(font);
        formLayout = new QFormLayout(loginGroup);
        formLayout->setObjectName("formLayout");
        usernameLabel = new QLabel(loginGroup);
        usernameLabel->setObjectName("usernameLabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, usernameLabel);

        usernameEdit = new QLineEdit(loginGroup);
        usernameEdit->setObjectName("usernameEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, usernameEdit);

        passwordLabel = new QLabel(loginGroup);
        passwordLabel->setObjectName("passwordLabel");
        passwordLabel->setFont(font);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, passwordLabel);

        passwordEdit = new QLineEdit(loginGroup);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, passwordEdit);


        verticalLayout->addWidget(loginGroup);

        loginButton = new QPushButton(LoginPage);
        loginButton->setObjectName("loginButton");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Ubuntu")});
        font3.setBold(true);
        loginButton->setFont(font3);

        verticalLayout->addWidget(loginButton);

        registerButton = new QPushButton(LoginPage);
        registerButton->setObjectName("registerButton");
        registerButton->setFont(font3);

        verticalLayout->addWidget(registerButton);

        statusLabel = new QLabel(LoginPage);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(statusLabel);

        spacerBottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(spacerBottom);


        retranslateUi(LoginPage);

        QMetaObject::connectSlotsByName(LoginPage);
    } // setupUi

    void retranslateUi(QWidget *LoginPage)
    {
        titleLabel->setText(QCoreApplication::translate("LoginPage", "\320\220\321\203\321\202\320\265\320\275\321\202\320\270\321\204\320\270\320\272\320\260\321\206\320\270\321\217", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("LoginPage", "> \320\235\320\265\320\276\320\261\321\205\320\276\320\264\320\270\320\274\320\276 \320\262\320\276\320\271\321\202\320\270 <", nullptr));
        loginGroup->setTitle(QCoreApplication::translate("LoginPage", "[ \320\243\321\207\321\221\321\202\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265 ]", nullptr));
        usernameLabel->setText(QCoreApplication::translate("LoginPage", "\320\233\320\276\320\263\320\270\320\275:", nullptr));
        usernameEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\273\320\276\320\263\320\270\320\275", nullptr));
        passwordLabel->setText(QCoreApplication::translate("LoginPage", "\320\237\320\260\321\200\320\276\320\273\321\214:", nullptr));
        passwordEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginPage", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginPage", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        statusLabel->setText(QString());
        (void)LoginPage;
    } // retranslateUi

};

namespace Ui {
    class LoginPage: public Ui_LoginPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINPAGE_H
