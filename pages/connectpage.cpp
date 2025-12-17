#include "connectpage.h"
#include "ui_connectpage.h"

#include <QMessageBox>
#include <QStyle>

ConnectPage::ConnectPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::ConnectPage)
{
    ui->setupUi(this);
    ui->statusLabel->setProperty("state", "error");
    connect(ui->connectButton, &QPushButton::clicked,
            this, &ConnectPage::onConnectClicked);
}

ConnectPage::~ConnectPage()
{
    delete ui;
}
// void ConnectPage::onConnectClicked()
// {
//     else
//     {
//         m_statusLabel->setText(tr(">>> CONNECTING... <<<"));
//         m_statusLabel->setStyleSheet(
//             "font-size: 12px; "
//             "color: #00ff41; "
//             "padding: 20px; "
//             "background: transparent;"
//             "letter-spacing: 2px;"
//         );
//         m_connectButton->setEnabled(false);
//         emit r_connect(host, port);
//     }
// }
void ConnectPage::onConnectClicked()
{
    const QString host = ui->hostEdit->text().trimmed();
    bool isCorrect = false;
    const quint16 port = ui->portEdit->text().toUShort(&isCorrect);

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
        ui->statusLabel->setText(tr(">>> CONNECTING... <<<"));
        ui->statusLabel->setProperty("state", "ok");
        ui->statusLabel->style()->polish(ui->statusLabel);

        ui->connectButton->setEnabled(false);
        emit r_connect(host, port);
    }
}

void ConnectPage::onSocketError(const QString &msg)
{
    ui->statusLabel->setText(tr(">>> ERROR: %1 <<<").arg(msg.toUpper()));
    ui->statusLabel->setProperty("state", "error");
    ui->statusLabel->style()->polish(ui->statusLabel);

    ui->connectButton->setEnabled(true);
}

// void ConnectPage::setupUI() //TODO edit
// {
//     QVBoxLayout *mainLayout = new QVBoxLayout(this);
//     mainLayout->setSpacing(30);
//     mainLayout->setContentsMargins(40, 40, 40, 40);
//     mainLayout->addStretch();

//     // Логотип/Заголовок
//     QLabel *titleLabel = new QLabel(tr("NEOBANK"), this);
//     titleLabel->setStyleSheet(
//         "font-size: 64px; "
//         "font-weight: 900; "
//         "color: #00ff41; "
//         "padding: 30px; "
//         "background: transparent;"
//         "letter-spacing: 8px;"
//     );
//     titleLabel->setAlignment(Qt::AlignCenter);
//     mainLayout->addWidget(titleLabel);

//     QLabel *subtitleLabel = new QLabel(tr(">>> CONNECTION REQUIRED <<<"), this);
//     subtitleLabel->setStyleSheet(
//         "font-size: 14px; "
//         "color: #ff00ff; "
//         "padding-bottom: 30px;"
//         "letter-spacing: 3px;"
//     );
//     subtitleLabel->setAlignment(Qt::AlignCenter);
//     mainLayout->addWidget(subtitleLabel);

//     // Группа с параметрами подключения
//     QGroupBox *connectGroup = new QGroupBox(tr("[ CONNECTION PARAMETERS ]"), this);
//     connectGroup->setStyleSheet(
//         "QGroupBox {"
//         "    background: rgba(10, 10, 10, 0.9);"
//         "    border: 4px solid #00ff41;"
//         "    border-radius: 1px;"
//         "    margin-top: 20px;"
//         "    padding-top: 24px;"
//         "    font-size: 16px;"
//         "    font-weight: bold;"
//         "    color: #00ff41;"
//         "}"
//     );
//     QFormLayout *formLayout = new QFormLayout(connectGroup);
//     formLayout->setSpacing(20);
//     formLayout->setContentsMargins(30, 30, 30, 30);

//     // Поле Хост
//     QLabel *hostLabel = new QLabel(tr("HOST:"), this);
//     hostLabel->setStyleSheet("font-size: 13px; font-weight: bold; color: #00ff41; letter-spacing: 2px;");
//     m_hostEdit = new QLineEdit(this);
//     m_hostEdit->setText("127.0.0.1");
//     m_hostEdit->setPlaceholderText(tr("SERVER ADDRESS"));
//     formLayout->addRow(hostLabel, m_hostEdit);

//     // Поле Порт
//     QLabel *portLabel = new QLabel(tr("PORT:"), this);
//     portLabel->setStyleSheet("font-size: 13px; font-weight: bold; color: #00ff41; letter-spacing: 2px;");
//     m_portEdit = new QLineEdit(this);
//     m_portEdit->setText("4433");
//     m_portEdit->setInputMask("00000;_");
//     m_portEdit->setPlaceholderText(tr("PORT NUMBER"));
//     formLayout->addRow(portLabel, m_portEdit);

//     mainLayout->addWidget(connectGroup);

//     // Кнопка подключения
//     m_connectButton = new QPushButton(tr("[ CONNECT ]"), this);
//     m_connectButton->setStyleSheet(
//         "QPushButton {"
//         "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
//         "        stop:0 #00ff41, stop:1 #00cc33);"
//         "    border: 4px solid #00ff41;"
//         "    border-radius: 1px;"
//         "    padding: 20px 50px;"
//         "    font-size: 16px;"
//         "    font-weight: 900;"
//         "    color: #000000;"
//         "    min-height: 28px;"
//         "    letter-spacing: 3px;"
//         "}"
//         "QPushButton:hover {"
//         "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
//         "        stop:0 #00ff88, stop:1 #00ff41);"
//         "    border: 4px solid #00ff88;"
//         "}"
//         "QPushButton:pressed {"
//         "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
//         "        stop:0 #00cc33, stop:1 #009922);"
//         "    border: 4px solid #00cc33;"
//         "    padding-top: 22px;"
//         "    padding-left: 52px;"
//         "}"
//     );
//     mainLayout->addWidget(m_connectButton);

//     // Лейбл статуса
//     m_statusLabel = new QLabel(tr(">>> NOT CONNECTED <<<"), this);
//     m_statusLabel->setStyleSheet(
//         "font-size: 12px; "
//         "color: #ff00ff; "
//         "padding: 20px; "
//         "background: transparent;"
//         "letter-spacing: 2px;"
//     );
//     m_statusLabel->setAlignment(Qt::AlignCenter);
//     mainLayout->addWidget(m_statusLabel);

//     mainLayout->addStretch();
// }

// void ConnectPage::setupConnections()
// {
//     connect(m_connectButton, &QPushButton::clicked,
//             this, &ConnectPage::onConnectClicked);
// }



// void ConnectPage::onSocketError(const QString &msg)
// {
//     m_statusLabel->setText(tr(">>> ERROR: %1 <<<").arg(msg.toUpper()));
//     m_statusLabel->setStyleSheet(
//         "font-size: 12px; "
//         "color: #ff00ff; "
//         "padding: 20px; "
//         "background: transparent;"
//         "letter-spacing: 2px;"
//     );
//     m_connectButton->setEnabled(true);
// }

