/********************************************************************************
** Form generated from reading UI file 'connectpage.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTPAGE_H
#define UI_CONNECTPAGE_H

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

class Ui_ConnectPage
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *spacerTop;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QGroupBox *connectGroup;
    QFormLayout *formLayout;
    QLabel *hostLabel;
    QLineEdit *hostEdit;
    QLabel *portLabel;
    QLineEdit *portEdit;
    QPushButton *connectButton;
    QLabel *statusLabel;
    QSpacerItem *spacerBottom;

    void setupUi(QWidget *ConnectPage)
    {
        if (ConnectPage->objectName().isEmpty())
            ConnectPage->setObjectName("ConnectPage");
        ConnectPage->resize(963, 629);
        ConnectPage->setStyleSheet(QString::fromUtf8("QWidget#ConnectPage {\n"
"    background-color: #ffffff;\n"
"	font-family: \"Ubuntu\", monospace;\n"
"}\n"
"\n"
"QLabel#titleLabel {\n"
"    font-size: 60px;\n"
"    font-weight: 900;\n"
"    padding: 30px;\n"
"    letter-spacing: 8px;\n"
"    color: #800000;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QLabel#subtitleLabel {\n"
"    font-size: 14px;\n"
"    padding-bottom: 30px;\n"
"    letter-spacing: 3px;\n"
"    color: #000000;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QGroupBox#connectGroup {\n"
"    background: qlineargradient(x1:0,y1:0,x2:0,y2:1,\n"
"        stop:0 #f2f2f2, stop:1 #d9d9d9);\n"
"    border: 2px solid #9e9e9e;\n"
"    border-radius: 4px;\n"
"    margin-top: 30px;          \n"
"    padding: 40px 20px 20px 20px; \n"
"    font-size: 16px;\n"
"    font-weight: 900;\n"
"    color: #000000;\n"
"    letter-spacing: 2px;\n"
"}\n"
"\n"
"QGroupBox#connectGroup::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    color: #00000"
                        "0; \n"
"    font-size: 18px;\n"
"    font-weight: 900;\n"
"    letter-spacing: 2px;\n"
"}\n"
"\n"
"QLineEdit#hostEdit,\n"
"QLineEdit#portEdit {\n"
"    background: #f5f5f5;\n"
"    border: 1px solid #cfcfcf;\n"
"    border-radius: 4px;\n"
"    padding: 8px 12px;\n"
"    color: #000000;\n"
"    font-size: 14px;\n"
"    selection-background-color: #cfcfcf;\n"
"    selection-color: #000000;\n"
"}\n"
"\n"
"QLineEdit#hostEdit:focus,\n"
"QLineEdit#portEdit:focus {\n"
"    border-color: #7a7a7a;\n"
"}\n"
"\n"
"QLabel#hostLabel,\n"
"QLabel#portLabel {\n"
"    color: #000000; \n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QPushButton#connectButton {\n"
"    background: qlineargradient(x1:0,y1:0,x2:0,y2:1,\n"
"        stop:0 #f2f2f2, stop:1 #d9d9d9);\n"
"    border: 2px solid #9e9e9e;\n"
"    border-radius: 4px;\n"
"    padding: 20px 50px;\n"
"    font-size: 16px;\n"
"    font-weight: 900;\n"
"    color: #000000;\n"
"    letter-spacing: 3px;\n"
"}\n"
"\n"
"QPushButto"
                        "n#connectButton:hover {\n"
"    background: qlineargradient(x1:0,y1:0,x2:0,y2:1,\n"
"        stop:0 #ffffff, stop:1 #e6e6e6);\n"
"    border-color: #7a7a7a;\n"
"}\n"
"\n"
"QPushButton#connectButton:pressed {\n"
"    background: qlineargradient(x1:0,y1:0,x2:0,y2:1,\n"
"        stop:0 #cfcfcf, stop:1 #bdbdbd);\n"
"}\n"
"\n"
"QLabel#statusLabel {\n"
"    font-size: 12px;\n"
"    padding: 20px;\n"
"    letter-spacing: 2px;\n"
"    color: #4facfe; \n"
"    background: transparent;\n"
"}\n"
"\n"
"QLabel#statusLabel[state=\"ok\"] {\n"
"    color: #00c853; \n"
"}\n"
"\n"
"QLabel#statusLabel[state=\"error\"] {\n"
"    color: #ff6b6b; \n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(ConnectPage);
        verticalLayout->setObjectName("verticalLayout");
        spacerTop = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(spacerTop);

        titleLabel = new QLabel(ConnectPage);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Ubuntu")});
        font.setWeight(QFont::Black);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QString::fromUtf8(""));
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        subtitleLabel = new QLabel(ConnectPage);
        subtitleLabel->setObjectName("subtitleLabel");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Ubuntu")});
        font1.setItalic(true);
        subtitleLabel->setFont(font1);
        subtitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(subtitleLabel);

        connectGroup = new QGroupBox(ConnectPage);
        connectGroup->setObjectName("connectGroup");
        formLayout = new QFormLayout(connectGroup);
        formLayout->setObjectName("formLayout");
        hostLabel = new QLabel(connectGroup);
        hostLabel->setObjectName("hostLabel");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Ubuntu")});
        font2.setBold(true);
        hostLabel->setFont(font2);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, hostLabel);

        hostEdit = new QLineEdit(connectGroup);
        hostEdit->setObjectName("hostEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, hostEdit);

        portLabel = new QLabel(connectGroup);
        portLabel->setObjectName("portLabel");
        portLabel->setFont(font2);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, portLabel);

        portEdit = new QLineEdit(connectGroup);
        portEdit->setObjectName("portEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, portEdit);


        verticalLayout->addWidget(connectGroup);

        connectButton = new QPushButton(ConnectPage);
        connectButton->setObjectName("connectButton");
        connectButton->setFont(font);

        verticalLayout->addWidget(connectButton);

        statusLabel = new QLabel(ConnectPage);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setFont(font1);
        statusLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(statusLabel);

        spacerBottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(spacerBottom);


        retranslateUi(ConnectPage);

        QMetaObject::connectSlotsByName(ConnectPage);
    } // setupUi

    void retranslateUi(QWidget *ConnectPage)
    {
        titleLabel->setText(QCoreApplication::translate("ConnectPage", "NEOBANK", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("ConnectPage", "> \320\242\321\200\320\265\320\261\321\203\320\265\321\202\321\201\321\217 \320\277\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265 <", nullptr));
        connectGroup->setTitle(QCoreApplication::translate("ConnectPage", "[ \320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\277\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\321\217 ]", nullptr));
        hostLabel->setText(QCoreApplication::translate("ConnectPage", "\320\245\320\276\321\201\321\202:", nullptr));
        hostEdit->setText(QCoreApplication::translate("ConnectPage", "127.0.0.1", nullptr));
        portLabel->setText(QCoreApplication::translate("ConnectPage", "\320\237\320\276\321\200\321\202:", nullptr));
        portEdit->setInputMask(QCoreApplication::translate("ConnectPage", "00000;_", nullptr));
        portEdit->setText(QCoreApplication::translate("ConnectPage", "4433", nullptr));
        connectButton->setText(QCoreApplication::translate("ConnectPage", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217", nullptr));
        statusLabel->setText(QCoreApplication::translate("ConnectPage", "> \320\235\320\265 \320\277\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\276 <", nullptr));
        (void)ConnectPage;
    } // retranslateUi

};

namespace Ui {
    class ConnectPage: public Ui_ConnectPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTPAGE_H
