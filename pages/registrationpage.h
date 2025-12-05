#ifndef REGISTRATIONPAGE_H
#define REGISTRATIONPAGE_H

#include <QWidget>
#include <QRegularExpressionValidator>
class SocketHandler;
class QLineEdit;
class QPushButton;
class QLabel;

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
    explicit RegistrationPage(QWidget *parent = nullptr);

signals:
    void loginPageRequested();
    void registrationRequested(const RegData &regData);

public slots:
    void onRegistrationError(const QString &error);
    void onRegistrationSuccess();

private slots:
    void onRegisterClicked();

private:

    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
    QLineEdit *m_passwordConfirmEdit;
    QLineEdit *m_emailEdit;
    QLineEdit *m_phoneEdit;
    QPushButton *m_backToLogin;
    QPushButton *m_registerButton;
    QLabel *m_statusLabel;

    QRegularExpression m_phoneRegex {R"(^\+375(25|29|33|44)\d{7}$)"};
    QRegularExpression m_emailRegex {R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)"};
};

#endif // REGISTRATIONPAGE_H
