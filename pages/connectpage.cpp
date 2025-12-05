#include "connectpage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QGroupBox>

ConnectPage::ConnectPage(QWidget *parent)
    : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);

    auto *titleLabel = new QLabel(tr("Подключение к серверу"), this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    auto *connectGroup = new QGroupBox(tr("Параметры подключения"), this);
    auto *formLayout = new QFormLayout(connectGroup);

    m_hostEdit = new QLineEdit(this);
    m_hostEdit->setText("127.0.0.1");
    m_hostEdit->setPlaceholderText(tr("Адрес сервера"));
    formLayout->addRow(tr("Хост:"), m_hostEdit);

    m_portEdit = new QLineEdit(this);
    m_portEdit->setText("4433");
    m_portEdit->setInputMask("00000;_");
    m_portEdit->setPlaceholderText(tr("Порт"));
    formLayout->addRow(tr("Порт:"), m_portEdit);

    mainLayout->addWidget(connectGroup);

    m_connectButton = new QPushButton(tr("Подключиться"), this);
    m_connectButton->setStyleSheet("padding: 10px; font-size: 14px;");
    mainLayout->addWidget(m_connectButton);

    m_statusLabel = new QLabel(tr("Не подключено"), this);
    m_statusLabel->setStyleSheet("color: gray; padding: 10px;");
    mainLayout->addWidget(m_statusLabel);

    mainLayout->addStretch();

    connect(m_connectButton, &QPushButton::clicked, this, &ConnectPage::onConnectClicked);
}

void ConnectPage::onConnectClicked()
{

    const QString host = m_hostEdit->text().trimmed();
    bool isCorrect = false;
    const quint16 port = m_portEdit->text().toUShort(&isCorrect);

    if (host.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Введите адрес сервера"));
    }
    else if (!isCorrect || port == 0) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Некорректный порт"));
    }
    else
    {
        m_statusLabel->setText(tr("Подключение..."));
        m_statusLabel->setStyleSheet("color: blue; padding: 10px;");
        m_connectButton->setEnabled(false);
        emit connectRequested(host, port);
    }
}

void ConnectPage::onSocketError(const QString &msg)
{
    m_statusLabel->setText(tr("Ошибка подключения: %1").arg(msg));
    m_statusLabel->setStyleSheet("color: red; padding: 10px;");
    m_connectButton->setEnabled(true);
}

