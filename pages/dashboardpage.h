#ifndef DASHBOARDPAGE_H
#define DASHBOARDPAGE_H

#include "ui_dashboardpage.h"
#include <QLabel>
#include <QPushButton>

class DashboardPage : public QWidget
{
    Q_OBJECT
public:
    explicit DashboardPage(QWidget *parent = nullptr);
    ~DashboardPage();
signals:
    void pr_accounts();
    void pr_transactions();
    void r_logout();

private:
    void setupConnections();
    Ui::DashboardPage *ui;
};

#endif // DASHBOARDPAGE_H

