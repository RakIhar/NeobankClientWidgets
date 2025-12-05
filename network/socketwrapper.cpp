#include "socketwrapper.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QtEndian>

#include "../protocols/protocolvalidator.h"

SocketHandler::SocketHandler(QObject *parent)
    : QObject{parent}
{
    connect(&m_socket, &QSslSocket::encrypted,
            this, &SocketHandler::onEncrypted);
    connect(&m_socket, &QSslSocket::readyRead,
            this, &SocketHandler::onReadyRead);
    connect(&m_socket, QOverload<const QList<QSslError>&>::of(&QSslSocket::sslErrors),
            this, &SocketHandler::onSslErrors);
    connect(&m_socket, &QSslSocket::errorOccurred,
            this, &SocketHandler::onErrorOccurred);
    connect(&m_socket, &QSslSocket::disconnected,
            this, [this](){ emit disconnected(); });
}

void SocketHandler::connectToServer(const QString &host, quint16 port)
{
    m_socket.connectToHostEncrypted(host, port);
}

void SocketHandler::disconnectFromServer()
{
    m_socket.disconnectFromHost();
}

void SocketHandler::sendData(const QByteArray &msg)
{
    if (m_socket.state() == QAbstractSocket::ConnectedState)
    {
        QJsonDocument doc;
        if (ProtocolValidator::validateMessage(msg, doc))
        {
            m_sentMsgs.append(doc.toJson(QJsonDocument::Compact));
            emit sentMessagesChanged();

            quint32 msgSize = msg.size();
            QByteArray packet;
            packet.resize(sizeof(quint32) + msgSize);
            qToBigEndian(msgSize, packet.data());
            memcpy(packet.data() + 4, msg.constData(), msgSize);
            m_socket.write(packet);
            m_socket.flush();
        }
        else
        {
            emit errorOccurred("Попытка отправить некорректный JSON");
            qWarning() << "Некорректный JSON(отпр):" << msg;
        }
    }
    else
    {
        emit errorOccurred("Не подключен к серверу");
    }
}

void SocketHandler::onReadyRead()
{
    m_buffer.append(m_socket.readAll());
    if (m_buffer.size() >= sizeof(quint32))
    {
        quint32 msgSize;
        memcpy(&msgSize, m_buffer.constData(), sizeof(quint32));
        msgSize = qFromBigEndian(msgSize);

        if (m_buffer.size() >=sizeof(quint32) + msgSize)
        {
            QByteArray msg = m_buffer.mid(sizeof(quint32), msgSize);
            m_buffer.remove(0, sizeof(quint32) + msgSize);
            processIncomingMessage(msg);
        }
    }
}

void SocketHandler::processIncomingMessage(const QByteArray &msg)
{
    QJsonDocument doc;
    if (ProtocolValidator::validateMessage(msg, doc))
    {
        m_receivedMsgs.append(doc.toJson(QJsonDocument::Compact));
        // emit receivedMessagesChanged();
        emit messageReceived(msg);
    }
    else
    {
        qWarning() << "Некорректный JSON(пол):" << msg;
    }
}

void SocketHandler::onEncrypted()
{
    qInfo() << "SSL соединение установлено(onEncrypted)";
    emit connected();
}

void SocketHandler::onSslErrors(const QList<QSslError> &errors)
{
    for (const auto &e : errors)
        qWarning() << "SSL ошибка:" << e.errorString();
    m_socket.ignoreSslErrors();
}

void SocketHandler::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Сетевая ошибка:" << error;
    emit errorOccurred(m_socket.errorString());
}


