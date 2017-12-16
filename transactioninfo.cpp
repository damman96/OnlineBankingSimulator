#include "transactioninfo.h"
#include "widget.h"

transactioninfo::transactioninfo()
{

}

int transactioninfo::dataTransaction()
{

}

QString transactioninfo::getCurrentDate()
{
    QDate currentDate = QDate::currentDate();
    QString _currentDate = currentDate.toString(Qt::SystemLocaleShortDate);
    return _currentDate;
}
