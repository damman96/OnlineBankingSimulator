#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QTableWidget>
#include "database.h"
#include "customerinfo.h"
#include "transactioninfo.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_loginButton_clicked();

    void on_logoutButton_clicked();

    void on_transferButton_clicked();

    void on_makeTransferButton_clicked();

public:
    QString username;
    QString password;

private:
    Ui::Widget *ui;
    database db;
    customerInfo ci;
    transactioninfo ti;
};

#endif // WIDGET_H
