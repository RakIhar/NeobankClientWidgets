#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

#include <QObject>
#include <QSslSocket>

class SocketWrapper : public QObject
{
    Q_OBJECT
public:
    explicit SocketWrapper(QObject *parent = nullptr);
    void send(const QByteArray &msg);
    void connect(const QString &host, quint16 port);
    void disconnect();

signals:
    void connected();
    void disconnected();
    void sent();
    void errorOccurred(const QString &msg);
    void received(const QByteArray &msg);

//==================================================//

private:
    QSslSocket m_socket;
    QByteArray m_buffer;

private slots:
    void onReadyRead();
};

#endif // SOCKETWRAPPER_H


