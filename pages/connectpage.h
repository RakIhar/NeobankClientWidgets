#ifndef CONNECTPAGE_H
#define CONNECTPAGE_H

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

namespace Ui { class ConnectPage; }

class ConnectPage : public QWidget
{
    Q_OBJECT
public:
    explicit ConnectPage(QWidget *parent = nullptr);
    ~ConnectPage();

signals:
    void r_connect(QString host, quint16 port);

public slots:
    void onSocketError(const QString &msg);

private slots:
    void onConnectClicked();

private:
    Ui::ConnectPage *ui;
};

#endif // CONNECTPAGE_H

