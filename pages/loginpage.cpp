#include "loginpage.h"

#include <QMessageBox>
#include <qstyle.h>

LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    ui->statusLabel->setProperty("state", "empty");
    ui->statusLabel->style()->polish(ui->statusLabel);
    setupConnections();
}

void LoginPage::reset()
{
    ui->statusLabel->clear();
    ui->statusLabel->setProperty("state", "empty");
    ui->statusLabel->style()->polish(ui->statusLabel);
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
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
        ui->statusLabel->setProperty("state", "loading");
        ui->statusLabel->style()->polish(ui->statusLabel);
        ui->loginButton->setEnabled(false);

        emit r_login(username, password);
    }
}

void LoginPage::onLoginError(const QString &reason)
{
    ui->statusLabel->setText(tr("> Ошибка: %1 <").arg(reason.toUpper()));
    ui->statusLabel->setProperty("state", "error");
    ui->statusLabel->style()->polish(ui->statusLabel);
    ui->loginButton->setEnabled(true);
}

