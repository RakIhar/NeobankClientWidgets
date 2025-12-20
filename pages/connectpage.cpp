#include "connectpage.h"
#include "ui_connectpage.h"

#include <QMessageBox>
#include <QStyle>

ConnectPage::ConnectPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::ConnectPage)
{
    ui->setupUi(this);

    m_connectionTimer = new QTimer(this);
    m_connectionTimer->setSingleShot(true);
    connect(m_connectionTimer, &QTimer::timeout, this, [this]{onSocketError(tr("Превышено время ожидания"));});

    ui->statusLabel->setProperty("state", "empty");
    ui->statusLabel->style()->polish(ui->statusLabel);
    connect(ui->connectButton, &QPushButton::clicked,
            this, &ConnectPage::onConnectClicked);
}

ConnectPage::~ConnectPage() { delete ui; }

void ConnectPage::reset()
{
    m_connectionTimer->stop();

    ui->hostEdit->setText(QStringLiteral("127.0.0.1"));
    ui->portEdit->setText(QStringLiteral("4433"));

    ui->statusLabel->setText(tr("> Не подключено <"));
    ui->statusLabel->setProperty("state", "empty");
    ui->statusLabel->style()->polish(ui->statusLabel);

    ui->connectButton->setEnabled(true);
}

void ConnectPage::onConnectClicked()
{
    const QString host = ui->hostEdit->text().trimmed();
    bool isCorrect = false;
    const quint16 port = ui->portEdit->text().toUShort(&isCorrect);
    constexpr int TIMEOUT_MS = 10000;
    if (host.isEmpty())
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Введите адрес сервера"));
    }
    else if (!isCorrect || port == 0)
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Некорректный порт"));
    }
    else
    {
        ui->statusLabel->setText(tr("> Подключение... <"));
        ui->statusLabel->setProperty("state", "loading");
        ui->statusLabel->style()->polish(ui->statusLabel);

        ui->connectButton->setEnabled(false);
        m_connectionTimer->start(TIMEOUT_MS);
        emit r_connect(host, port);
    }
}

void ConnectPage::onSocketError(const QString &msg)
{
    ui->statusLabel->setText(tr("> Ошибка: %1 <").arg(msg.toUpper()));
    ui->statusLabel->setProperty("state", "error");
    ui->statusLabel->style()->polish(ui->statusLabel);

    ui->connectButton->setEnabled(true);
}

void ConnectPage::stopConnectionTimer()
{
    m_connectionTimer->stop();
}
