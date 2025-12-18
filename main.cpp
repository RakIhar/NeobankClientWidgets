#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QFont>
#include <QDebug>

//готово полностью:
//connectpage.cpp/h
//loginpage.cpp/h
//registrationpage.cpp/h

//добавить:
//dashboard.cpp/h общий баланс - со всех счетов в одной валюте

//улучшено
//десериализатор для транзакций
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qssFile(":/styles/main.qss");
    if (!qssFile.open(QFile::ReadOnly | QFile::Text)) {
        qssFile.setFileName("styles/styles.qss");
        if (!qssFile.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "Warning: stylesheet not found in resources or relative path";
        }
    }
    if (qssFile.isOpen()) {
        QTextStream ts(&qssFile);
        a.setStyleSheet(ts.readAll());
        qssFile.close();
    }
    MainWindow w;
    w.show();
    return a.exec();
}
