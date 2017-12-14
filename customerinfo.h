#ifndef CUSTOMERINFO_H
#define CUSTOMERINFO_H

#include <QSqlQuery>

class customerInfo
{
public:
    customerInfo();
    dataLogin(QString username, QString password);
    QString getName();
    QString getUsername();
    QString getSurname();
    double getBalance();
    QString getAccountNumber();
    int getTransactionsLimit();
    int getOperationsLimit();
    int getCredit();

private:
    static const int defNOWL = 3;
    QString _username;
    QString _name;
    QString _surname;
    double _balance;
    QString _accountNumber;
    int _transactionsLimit;
    int _operationsLimit;
    int _credit;
    int _nowl;
};

#endif // CUSTOMERINFO_H
