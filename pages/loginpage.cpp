#include "loginpage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QGroupBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QTimer>

LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);

    auto *titleLabel = new QLabel(tr("Вход в систему"), this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    auto *loginGroup = new QGroupBox(tr("Учетные данные"), this);
    auto *formLayout = new QFormLayout(loginGroup);

    m_usernameEdit = new QLineEdit(this);
    m_usernameEdit->setPlaceholderText(tr("Имя пользователя"));
    formLayout->addRow(tr("Логин:"), m_usernameEdit);

    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_passwordEdit->setPlaceholderText(tr("Пароль"));
    formLayout->addRow(tr("Пароль:"), m_passwordEdit);

    mainLayout->addWidget(loginGroup);

    auto *buttonsLayout = new QHBoxLayout;
    m_loginButton = new QPushButton(tr("Войти"), this);
    m_loginButton->setStyleSheet("padding: 10px; font-size: 14px;");
    m_registerButton = new QPushButton(tr("Регистрация"), this);
    m_registerButton->setStyleSheet("padding: 10px; font-size: 14px;");
    buttonsLayout->addWidget(m_loginButton);
    buttonsLayout->addWidget(m_registerButton);
    mainLayout->addLayout(buttonsLayout);

    m_statusLabel = new QLabel("", this);
    m_statusLabel->setStyleSheet("color: gray; padding: 10px;");
    mainLayout->addWidget(m_statusLabel);

    mainLayout->addStretch();

    connect(m_loginButton, &QPushButton::clicked, this, &LoginPage::onLoginClicked);
    connect(m_registerButton, &QPushButton::clicked, this, &LoginPage::onRegisterClicked);
}

void LoginPage::onLoginClicked()
{
    const QString username = m_usernameEdit->text().trimmed();
    const QString password = m_passwordEdit->text();

    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Заполните все поля"));
    }
    else
    {
        m_statusLabel->setText(tr("Отправка запроса..."));
        m_statusLabel->setStyleSheet("color: blue; padding: 10px;");
        m_loginButton->setEnabled(false);

        emit loginRequested(username, password);
    }
}

void LoginPage::onRegisterClicked()
{
    emit registrationPageRequested();
}

void LoginPage::onLoginError(const QString &reason)
{
    m_statusLabel->setText(reason);
    m_statusLabel->setStyleSheet("color: red; padding: 10px;");
    m_loginButton->setEnabled(true);
}
