#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

#include <QObject>
#include <QSslSocket>

class SocketHandler : public QObject
{
    Q_OBJECT
public:
    explicit SocketHandler(QObject *parent = nullptr);

    void sendData(const QByteArray &msg);
    void connectToServer(const QString &host, quint16 port);
    void disconnectFromServer();

    QStringList receivedMessages() const { return m_receivedMsgs; }
    QStringList sentMessages() const { return m_sentMsgs; }

private:
    QSslSocket m_socket;
    QStringList m_receivedMsgs;
    QStringList m_sentMsgs;
    QByteArray m_buffer;

private slots:
    void onEncrypted();
    void onSslErrors(const QList<QSslError> &errors);
    void onErrorOccurred(QAbstractSocket::SocketError error);

    void onReadyRead();
    void processIncomingMessage(const QByteArray &data);

signals:
    void connected();
    void disconnected();
    void receivedMessagesChanged();
    void sentMessagesChanged();
    void errorOccurred(const QString &msg);
    void messageReceived(const QByteArray &msg);
};

#endif // SOCKETWRAPPER_H


