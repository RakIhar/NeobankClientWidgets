#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include "ui_loginpage.h"

class LoginPage : public QWidget
{
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);
    void reset();

signals:
    void r_login(const QString &username, const QString &password);
    void pr_registration();

public slots:
    void onLoginError(const QString &reason);

private slots:
    void onLoginClicked();

private:
    void setupConnections();
    Ui::LoginPage *ui;
};

#endif // LOGINPAGE_H

