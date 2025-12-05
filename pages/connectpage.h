#ifndef CONNECTPAGE_H
#define CONNECTPAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QLabel;
QT_END_NAMESPACE

class SocketHandler;

class ConnectPage : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectPage(QWidget *parent = nullptr);

signals:
    void connectRequested(QString host, quint16 port);

private slots:
    void onConnectClicked();

public slots:
    void onSocketError(const QString &msg);

private:
    QLineEdit *m_hostEdit;
    QLineEdit *m_portEdit;
    QPushButton *m_connectButton;
    QLabel *m_statusLabel;
};

#endif // CONNECTPAGE_H

