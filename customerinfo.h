#ifndef CUSTOMERINFO_H
#define CUSTOMERINFO_H

#include <QSqlQuery>

class customerInfo
{
public:
    customerInfo();
    int dataLogin(QString username, QString password);
    bool changePassword(QString password,QString oldPassword,QString newPassword);
    QString getName();
    QString getUsername();
    QString getSurname();
    double getBalance();
    QString getAccountNumber();
    double getTransactionsLimit();
    double getTransactions();
    int getOperationsLimit();
    int getOperations();
    int getCredit();

private:
    static const int defNOWL = 3;
    QString _username;
    QString _name;
    QString _surname;
    QString _accountNumber;
    double _balance;
    int _transactionsLimit;
    int _operationsLimit;
    int _credit;
    int _nowl;
    double _transactions;
    int _operations;
};

#endif // CUSTOMERINFO_H
