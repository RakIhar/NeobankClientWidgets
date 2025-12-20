#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include "ui_loginpage.h"
#include "../services/authservice.h"

class LoginPage : public QWidget
{
    Q_OBJECT
public:
    explicit LoginPage(AuthService *authService, QWidget *parent = nullptr);
    ~LoginPage();;
    void reset();

signals:
    void pr_registration();

private slots:
    void onLoginClicked();
    void onLoginError(const QString &reason);

private:
    void setupConnections();
    AuthService *m_authService;
    Ui::LoginPage *ui;
};

#endif // LOGINPAGE_H

