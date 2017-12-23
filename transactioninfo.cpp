#include "transactioninfo.h"
#include "widget.h"

transactioninfo::transactioninfo()
{

}

int transactioninfo::getRecipientData(QString currentDate, double amount, QString recipientName, QString title, QString accountNumber)
{
    QSqlQuery qry;

    if(qry.exec("SELECT BALANCE, ACCOUNT_NUMBER FROM customers WHERE ACCOUNT_NUMBER='"+accountNumber+"'"))
    {
        if(qry.next())
        {
            recipientBalance = qry.value(0).toDouble();
            recipientAccountNumber = qry.value(1).toString();
        }
    }
}

QString transactioninfo::getCurrentDate()
{
    QDate currentDate = QDate::currentDate();
    QString _currentDate = currentDate.toString(Qt::SystemLocaleShortDate);
    return _currentDate;
}
