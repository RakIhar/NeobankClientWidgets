#include "loginpage.h"

#include <QMessageBox>

LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    setupConnections();
}

void LoginPage::reset()
{
    ui->statusLabel->setText(tr(""));
    ui->statusLabel->setStyleSheet(
        "font-size: 12px; "
        "color: #4facfe; "
        "padding: 20px; "
        "background: transparent;"
        "letter-spacing: 2px;"
    );
    ui->usernameEdit->setText("");
    ui->passwordEdit->setText("");
    ui->loginButton->setEnabled(true);
    ui->registerButton->setEnabled(true);
}

void LoginPage::setupConnections()
{
    connect(ui->loginButton, &QPushButton::clicked,
            this, &LoginPage::onLoginClicked);

    connect(ui->registerButton, &QPushButton::clicked, this,
    [this]{
        emit pr_registration();
    });
}

void LoginPage::onLoginClicked()
{
    const QString username = ui->usernameEdit->text().trimmed();
    const QString password = ui->passwordEdit->text();

    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Заполните все поля"));
    }
    else
    {
        ui->statusLabel->setText(tr("> Аутентификация... <"));
        ui->statusLabel->setStyleSheet(
            "font-size: 12px; "
            "color: #4facfe; "
            "padding: 20px; "
            "background: transparent;"
            "letter-spacing: 2px;"
        );
        ui->loginButton->setEnabled(false);

        emit r_login(username, password);
    }
}

void LoginPage::onLoginError(const QString &reason)
{
    ui->statusLabel->setText(tr(">>> Ошибка: %1 <<<").arg(reason.toUpper()));
    ui->statusLabel->setStyleSheet(
        "font-size: 12px; "
        "color: #ff6b6b; "
        "padding: 20px; "
        "background: transparent;"
        "letter-spacing: 2px;"
    );
    ui->loginButton->setEnabled(true);
}

