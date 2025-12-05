#include "transactionspage.h"
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

TransactionsPage::TransactionsPage(SocketHandler *client, QWidget *parent)
    : QWidget(parent)
    , m_client(client)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);

    // Заголовок
    auto *titleLabel = new QLabel(tr("История транзакций"), this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    // Список транзакций
    auto *transactionsGroup = new QGroupBox(tr("Транзакции"), this);
    auto *transactionsLayout = new QVBoxLayout(transactionsGroup);
    m_transactionsList = new QListWidget(this);
    transactionsLayout->addWidget(m_transactionsList);
    mainLayout->addWidget(transactionsGroup);

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
    connect(m_backButton, &QPushButton::clicked, this, &TransactionsPage::onBackClicked);
    connect(m_refreshButton, &QPushButton::clicked, this, &TransactionsPage::onRefreshClicked);

    refreshTransactions();
}

void TransactionsPage::refreshTransactions()
{
    if (!m_client) {
        m_statusLabel->setText(tr("Клиент не инициализирован"));
        return;
    }

    // Формируем запрос на получение транзакций
    QJsonObject request;
    request["type"] = "transaction.list";
    request["id"] = QString::number(QDateTime::currentMSecsSinceEpoch());
    request["payload"] = QJsonObject();

    QJsonDocument doc(request);
    m_client->sendData(doc.toJson(QJsonDocument::Compact));

    m_statusLabel->setText(tr("Загрузка транзакций..."));
    m_statusLabel->setStyleSheet("color: blue; padding: 10px;");

    // TODO: обработать ответ от сервера
    // Пока показываем заглушку
    m_transactionsList->clear();
    m_transactionsList->addItem(tr("01.01.2024 - Пополнение: +1000.00 ₽"));
    m_transactionsList->addItem(tr("02.01.2024 - Перевод: -500.00 ₽"));
    m_transactionsList->addItem(tr("03.01.2024 - Покупка: -250.50 ₽"));
}

void TransactionsPage::onBackClicked()
{
    emit backToDashboard();
}

void TransactionsPage::onRefreshClicked()
{
    refreshTransactions();
}

