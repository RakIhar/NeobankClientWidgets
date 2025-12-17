/********************************************************************************
** Form generated from reading UI file 'registrationpage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATIONPAGE_H
#define UI_REGISTRATIONPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistrationPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QGroupBox *registerGroup;
    QFormLayout *formLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameEdit;
    QLabel *emailLabel;
    QLineEdit *emailEdit;
    QLabel *phoneLabel;
    QLineEdit *phoneEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QLabel *passwordConfirmLabel;
    QLineEdit *passwordConfirmEdit;
    QHBoxLayout *buttonsLayout;
    QPushButton *backToLogin;
    QSpacerItem *hSpacer;
    QPushButton *registerButton;
    QLabel *statusLabel;

    void setupUi(QWidget *RegistrationPage)
    {
        if (RegistrationPage->objectName().isEmpty())
            RegistrationPage->setObjectName("RegistrationPage");
        RegistrationPage->resize(900, 700);
        verticalLayout = new QVBoxLayout(RegistrationPage);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(RegistrationPage);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(30);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        subtitleLabel = new QLabel(RegistrationPage);
        subtitleLabel->setObjectName("subtitleLabel");
        QFont font1;
        font1.setItalic(true);
        subtitleLabel->setFont(font1);
        subtitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(subtitleLabel);

        registerGroup = new QGroupBox(RegistrationPage);
        registerGroup->setObjectName("registerGroup");
        formLayout = new QFormLayout(registerGroup);
        formLayout->setObjectName("formLayout");
        usernameLabel = new QLabel(registerGroup);
        usernameLabel->setObjectName("usernameLabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, usernameLabel);

        usernameEdit = new QLineEdit(registerGroup);
        usernameEdit->setObjectName("usernameEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, usernameEdit);

        emailLabel = new QLabel(registerGroup);
        emailLabel->setObjectName("emailLabel");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, emailLabel);

        emailEdit = new QLineEdit(registerGroup);
        emailEdit->setObjectName("emailEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, emailEdit);

        phoneLabel = new QLabel(registerGroup);
        phoneLabel->setObjectName("phoneLabel");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, phoneLabel);

        phoneEdit = new QLineEdit(registerGroup);
        phoneEdit->setObjectName("phoneEdit");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, phoneEdit);

        passwordLabel = new QLabel(registerGroup);
        passwordLabel->setObjectName("passwordLabel");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, passwordLabel);

        passwordEdit = new QLineEdit(registerGroup);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, passwordEdit);

        passwordConfirmLabel = new QLabel(registerGroup);
        passwordConfirmLabel->setObjectName("passwordConfirmLabel");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, passwordConfirmLabel);

        passwordConfirmEdit = new QLineEdit(registerGroup);
        passwordConfirmEdit->setObjectName("passwordConfirmEdit");
        passwordConfirmEdit->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, passwordConfirmEdit);


        verticalLayout->addWidget(registerGroup);

        buttonsLayout = new QHBoxLayout();
        buttonsLayout->setObjectName("buttonsLayout");
        backToLogin = new QPushButton(RegistrationPage);
        backToLogin->setObjectName("backToLogin");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Ubuntu")});
        font2.setBold(true);
        backToLogin->setFont(font2);

        buttonsLayout->addWidget(backToLogin);

        hSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonsLayout->addItem(hSpacer);

        registerButton = new QPushButton(RegistrationPage);
        registerButton->setObjectName("registerButton");
        registerButton->setFont(font2);

        buttonsLayout->addWidget(registerButton);


        verticalLayout->addLayout(buttonsLayout);

        statusLabel = new QLabel(RegistrationPage);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);


        retranslateUi(RegistrationPage);

        QMetaObject::connectSlotsByName(RegistrationPage);
    } // setupUi

    void retranslateUi(QWidget *RegistrationPage)
    {
        titleLabel->setText(QCoreApplication::translate("RegistrationPage", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("RegistrationPage", "> \320\227\320\260\320\277\320\276\320\273\320\275\320\270\321\202\320\265 \321\204\320\276\321\200\320\274\321\203 \321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\320\270 <", nullptr));
        registerGroup->setTitle(QCoreApplication::translate("RegistrationPage", "[ \320\224\320\260\320\275\320\275\321\213\320\265 \321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\320\270 ]", nullptr));
        usernameLabel->setText(QCoreApplication::translate("RegistrationPage", "\320\233\320\276\320\263\320\270\320\275:", nullptr));
        emailLabel->setText(QCoreApplication::translate("RegistrationPage", "E-mail:", nullptr));
        phoneLabel->setText(QCoreApplication::translate("RegistrationPage", "\320\235\320\276\320\274\320\265\321\200 \321\202\320\265\320\273\320\265\321\204\320\276\320\275\320\260:", nullptr));
        passwordLabel->setText(QCoreApplication::translate("RegistrationPage", "\320\237\320\260\321\200\320\276\320\273\321\214:", nullptr));
        passwordConfirmLabel->setText(QCoreApplication::translate("RegistrationPage", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\266\320\264\320\265\320\275\320\270\320\265 \320\277\320\260\321\200\320\276\320\273\321\217:", nullptr));
        backToLogin->setText(QCoreApplication::translate("RegistrationPage", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        registerButton->setText(QCoreApplication::translate("RegistrationPage", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        (void)RegistrationPage;
    } // retranslateUi

};

namespace Ui {
    class RegistrationPage: public Ui_RegistrationPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATIONPAGE_H
