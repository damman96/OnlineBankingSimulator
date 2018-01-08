#ifndef TRANSACTIONINFO_H
#define TRANSACTIONINFO_H

#include <QDate>
#include <QSqlQuery>
#include "customerinfo.h"

class transactioninfo
{
public:
    transactioninfo();
    QString getCurrentDate();
    bool checkAccountBalance(double balance, double amount);
    void getRecipientData(QString accountNumber);
    void updateRecipient(double amount, QString accountNumber);
    void updateSender(double amount, QString accountNumber);
    void updateRecipientTransactions(double amount, QString title);
    void updateSenderTransactions(double amount, QString title, QString person);
    void getSenderData(QString senderName, QString senderUsername, QString senderSurname, QString senderAccNumber, double senderBalance, int senderTransactions, int senderOperations);
    void updateTransactions(QString Username);
    void updateOperations(QString Username);

private:   
    QString _currentDate;
    double recipientBalance, _senderBalance;

    QString recipientAccountNumber, recipientUsername;
    QString _senderName, _senderUsername, _senderSurname, _senderAccNumber;

    int _senderTransactions, _senderOperations;

    customerInfo custInfo;
};

#endif // TRANSACTIONINFO_H
