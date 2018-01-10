#ifndef CUSTOMERINFO_H
#define CUSTOMERINFO_H

#include <QSqlQuery>

class customerInfo
{
public:
    customerInfo();
    int getLoginData(QString username, QString password);
    void getPersonalInformation(QString username);
    bool changePassword(QString password,QString oldPassword,QString newPassword);
    bool changeTransactionsLimit(QString username, QString oldLimit, QString newLimit);
    bool changeOperationsLimit(QString username, QString oldLimit, QString newLimit);
    QString getCurrentDate();
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
    QString getLastLoginDate();
    void udpatelastLoginDate(QString username);

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

    QString _lastLoginDate, loginDate;
};

#endif // CUSTOMERINFO_H
