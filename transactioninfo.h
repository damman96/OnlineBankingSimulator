#ifndef TRANSACTIONINFO_H
#define TRANSACTIONINFO_H

#include <QDate>
#include <QSqlQuery>

class transactioninfo
{
public:
    transactioninfo();
    QString getCurrentDate();
    int dataTransaction();

private:
    QString _currentDate;
};

#endif // TRANSACTIONINFO_H
