#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QLabel;
QT_END_NAMESPACE

class SocketHandler;

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);

signals:
    void loginRequested(const QString &username, const QString &password);
    void registrationPageRequested();

private slots:
    void onLoginClicked();
    void onRegisterClicked();

public slots:
    // void onLoginSuccess();
    void onLoginError(const QString &reason); //обновить интерфейс

private:
    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
    QPushButton *m_loginButton;
    QPushButton *m_registerButton;
    QLabel *m_statusLabel;
};

#endif // LOGINPAGE_H

