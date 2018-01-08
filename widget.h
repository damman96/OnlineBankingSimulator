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

    void on_backButton_clicked();

    void on_settingsButton_clicked();

    void on_backSettingsButton_clicked();

    void on_passwordChangeButton_clicked();

    void on_limitChangeButton_clicked();

    void on_limitOperationChangeButton_clicked();

public:
    QString username, password;

    QString _name, _username, _surname, _accountNumber;
    double _balance;

    QString amountString, recipientString, title,  recipientAccountNumber, currentDate;
    double amount;

    QString oldPassword, newPassword;

    double transactionsLimit, transactions;
    int operationsLimit, operations;

    QString oldLimit, newLimit, oldOperLimit, newOperLimit;

private:
    Ui::Widget *ui;
    database db;
    customerInfo ci;
    transactioninfo ti;
};

#endif // WIDGET_H
