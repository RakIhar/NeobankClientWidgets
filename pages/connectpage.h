#ifndef CONNECTPAGE_H
#define CONNECTPAGE_H

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
namespace Ui { class ConnectPage; }

class ConnectPage : public QWidget
{
    Q_OBJECT
public:
    explicit ConnectPage(QWidget *parent = nullptr);
    ~ConnectPage();
    void reset();
    void stopConnectionTimer();

signals:
    void r_connect(QString host, quint16 port);

public slots:
    void onSocketError(const QString &msg);

private slots:
    void onConnectClicked();

private:
    Ui::ConnectPage *ui;
    QTimer *m_connectionTimer = nullptr;
};

#endif // CONNECTPAGE_H

