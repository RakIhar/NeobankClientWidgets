#include "accountspage.h"
#include "../network/socketwrapper.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

AccountsPage::AccountsPage(SocketHandler *client, QWidget *parent)
    : QWidget(parent)
    , m_client(client)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);

    // Заголовок
    auto *titleLabel = new QLabel(tr("Мои счета"), this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    // Список счетов
    auto *accountsGroup = new QGroupBox(tr("Счета"), this);
    auto *accountsLayout = new QVBoxLayout(accountsGroup);
    m_accountsList = new QListWidget(this);
    accountsLayout->addWidget(m_accountsList);
    mainLayout->addWidget(accountsGroup);

    // Кнопки
    auto *buttonsLayout = new QHBoxLayout;
    m_backButton = new QPushButton(tr("Назад"), this);
    m_backButton->setStyleSheet("padding: 10px; font-size: 14px;");
    m_refreshButton = new QPushButton(tr("Обновить"), this);
    m_refreshButton->setStyleSheet("padding: 10px; font-size: 14px;");
    buttonsLayout->addWidget(m_backButton);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(m_refreshButton);
    mainLayout->addLayout(buttonsLayout);

    // Статус
    m_statusLabel = new QLabel("", this);
    m_statusLabel->setStyleSheet("color: gray; padding: 10px;");
    mainLayout->addWidget(m_statusLabel);

    // Подключения
    connect(m_backButton, &QPushButton::clicked, this, &AccountsPage::onBackClicked);
    connect(m_refreshButton, &QPushButton::clicked, this, &AccountsPage::onRefreshClicked);

    refreshAccounts();
}

void AccountsPage::refreshAccounts()
{
    if (!m_client) {
        m_statusLabel->setText(tr("Клиент не инициализирован"));
        return;
    }

    // Формируем запрос на получение счетов
    QJsonObject request;
    request["type"] = "account.list";
    request["id"] = QString::number(QDateTime::currentMSecsSinceEpoch());
    request["payload"] = QJsonObject();

    QJsonDocument doc(request);
    m_client->sendData(doc.toJson(QJsonDocument::Compact));

    m_statusLabel->setText(tr("Загрузка счетов..."));
    m_statusLabel->setStyleSheet("color: blue; padding: 10px;");

    // TODO: обработать ответ от сервера
    // Пока показываем заглушку
    m_accountsList->clear();
    m_accountsList->addItem(tr("Счет 1: 1000.00 ₽"));
    m_accountsList->addItem(tr("Счет 2: 2500.50 ₽"));
}

void AccountsPage::onBackClicked()
{
    emit backToDashboard();
}

void AccountsPage::onRefreshClicked()
{
    refreshAccounts();
}

