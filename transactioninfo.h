#ifndef TRANSACTIONINFO_H
#define TRANSACTIONINFO_H

#include <QDate>

class transactioninfo
{
public:
    transactioninfo();
    QString getCurrentDate();

private:
    QString _currentDate;
};

#endif // TRANSACTIONINFO_H
