#ifndef REGISTRATIONPAGE_H
#define REGISTRATIONPAGE_H

#include "ui_registrationpage.h"
#include <QRegularExpressionValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "../services/authservice.h"

struct RegData
{
    QString username;
    QString email;
    QString phone;
    QString password;
};

class RegistrationPage : public QWidget
{
    Q_OBJECT
public:
    explicit RegistrationPage(AuthService *authService, QWidget *parent = nullptr);
    ~RegistrationPage();;
    void reset();

signals:
    void pr_login();

private slots:
    void onRegisterClicked();
    void onRegistrationError(const QString &error);
    void onRegistrationSuccess();

private:
    void setupConnections();
    AuthService *m_authService;
    Ui::RegistrationPage *ui;
    QRegularExpression m_phoneRegex {R"(^\+375(25|29|33|44)\d{7}$)"};
    QRegularExpression m_emailRegex {R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)"};
};

#endif // REGISTRATIONPAGE_H
