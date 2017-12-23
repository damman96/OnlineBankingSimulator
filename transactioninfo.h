#ifndef TRANSACTIONINFO_H
#define TRANSACTIONINFO_H

#include <QDate>
#include <QSqlQuery>

class transactioninfo
{
public:
    transactioninfo();
    QString getCurrentDate();
    int getRecipientData(QString currentDate, double amount, QString recipientName, QString title, QString accountNumber);

private:
    QString _currentDate;
    double recipientBalance;
    QString recipientAccountNumber;
};

#endif // TRANSACTIONINFO_H
