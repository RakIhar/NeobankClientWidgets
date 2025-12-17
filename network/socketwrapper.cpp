#include "socketwrapper.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QtEndian>
#include <QObject>

SocketWrapper::SocketWrapper(QObject *parent)
    : QObject{parent}
{
    QObject::connect(&m_socket, &QSslSocket::encrypted, this,
    [this]{
        qInfo() << "SSL соединение установлено(onEncrypted)";
        emit connected();
    });

    QObject::connect(&m_socket, QOverload<const QList<QSslError>&>::of(&QSslSocket::sslErrors), this,
    [this](const QList<QSslError> &errors){
        for (const auto &e : errors)
            qWarning() << "SSL ошибка:" << e.errorString();
        m_socket.ignoreSslErrors();
    });

    QObject::connect(&m_socket, &QSslSocket::errorOccurred, this,
    [this](QAbstractSocket::SocketError error){
        qWarning() << "Сетевая ошибка:" << error;
        emit errorOccurred(m_socket.errorString());
    });

    QObject::connect(&m_socket, &QSslSocket::disconnected, this,
    [this]{
        emit disconnected();
    });

    QObject::connect(&m_socket, &QSslSocket::readyRead,
                     this, &SocketWrapper::onReadyRead);
}

void SocketWrapper::connect(const QString &host, quint16 port)
{
    m_socket.connectToHostEncrypted(host, port);
}

void SocketWrapper::disconnect()
{
    m_socket.disconnectFromHost();
}

void SocketWrapper::send(const QByteArray &msg)
{
    if (m_socket.state() == QAbstractSocket::ConnectedState)
    {
        quint32 msgSize = msg.size();
        QByteArray packet;
        packet.resize(sizeof(quint32) + msgSize);
        qToBigEndian(msgSize, packet.data());
        memcpy(packet.data() + 4, msg.constData(), msgSize);
        m_socket.write(packet);
        m_socket.flush();
        emit sent();
    }
    else
    {
        emit errorOccurred("Не подключен к серверу");
    }
}

void SocketWrapper::onReadyRead()
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
            emit received(msg);
        }
    }
}
