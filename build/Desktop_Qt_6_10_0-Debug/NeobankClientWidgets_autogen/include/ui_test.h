/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Test
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *Test)
    {
        if (Test->objectName().isEmpty())
            Test->setObjectName("Test");
        Test->resize(400, 300);
        pushButton = new QPushButton(Test);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(190, 130, 94, 26));

        retranslateUi(Test);

        QMetaObject::connectSlotsByName(Test);
    } // setupUi

    void retranslateUi(QWidget *Test)
    {
        Test->setWindowTitle(QCoreApplication::translate("Test", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("Test", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Test: public Ui_Test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
