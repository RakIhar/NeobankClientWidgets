#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QFont>

int main(int argc, char *argv[])
{
    //TODO добавить лимиты в счета
    //TODO добавить удаление счетов
    //TODO добавить выбор валют
    QApplication a(argc, argv);
    QFont appFont("Ubuntu");
    a.setFont(appFont);
    QFile qssFile("styles/styles.qss");
    if (qssFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&qssFile);
        a.setStyleSheet(ts.readAll());
        qssFile.close();
    }
    MainWindow w;
    w.show();
    return a.exec();
}
