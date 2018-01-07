#include "transactioninfo.h"
#include "widget.h"

transactioninfo::transactioninfo()
{

}

void transactioninfo::getRecipientData(QString accountNumber)
{
    QSqlQuery qry;

    if(qry.exec("SELECT BALANCE, ACCOUNT_NUMBER, USERNAME FROM customers WHERE ACCOUNT_NUMBER='"+accountNumber+"'"))
    {
        if(qry.next())
        {
            recipientBalance = qry.value(0).toDouble();
            recipientAccountNumber = qry.value(1).toString();
            recipientUsername = qry.value(2).toString();
        }
    }
}

void transactioninfo::getSenderData(QString senderName, QString senderUsername, QString senderSurname, QString senderAccNumber, double senderBalance)
{
    _senderName = senderName;
    _senderUsername = senderUsername;
    _senderSurname = senderSurname;
    _senderAccNumber = senderAccNumber;
    _senderBalance = senderBalance;

}

void transactioninfo::updateRecipient(double amount, QString accountNumber)
{
    recipientBalance+=amount;
    QString recipientBalanceString = QString::number(recipientBalance);
    QSqlQuery qry;
    qry.exec("UPDATE customers SET BALANCE='"+recipientBalanceString+"' WHERE ACCOUNT_NUMBER='"+accountNumber+"'");
}

void transactioninfo::updateSender(double amount, QString accountNumber)
{
    _senderBalance-=amount;
    QString senderBalanceString = QString::number(_senderBalance);
    QSqlQuery qry;
    qry.exec("UPDATE customers SET BALANCE='"+senderBalanceString+"' WHERE ACCOUNT_NUMBER='"+accountNumber+"'");
}

void transactioninfo::updateRecipientTransactions(double amount, QString title)
{
    QString currentDate = getCurrentDate();
    QString sender = _senderName + " " + _senderSurname;

    QSqlQuery qry;
    qry.prepare("INSERT INTO transactions (USERNAME, DATE, PERSON, ACCNUMBER, TITLE, KINDOFOPER, AMOUNT) VALUES (?,?,?,?,?,?,?)");
    qry.addBindValue(recipientUsername);
    qry.addBindValue(currentDate);
    qry.addBindValue(sender);
    qry.addBindValue(_senderAccNumber);
    qry.addBindValue(title);
    qry.addBindValue("Przelew");
    qry.addBindValue(amount);
    qry.exec();
}

void transactioninfo::updateSenderTransactions(double amount, QString title, QString person)
{
    QString currentDate = getCurrentDate();
    QString amountString = QString::number(amount);
    QString amntStr = "-" + amountString;
    QSqlQuery qry;
    qry.prepare("INSERT INTO transactions (USERNAME, DATE, PERSON, ACCNUMBER, TITLE, KINDOFOPER, AMOUNT) VALUES (?,?,?,?,?,?,?)");
    qry.addBindValue(_senderUsername);
    qry.addBindValue(currentDate);
    qry.addBindValue(person);
    qry.addBindValue(recipientAccountNumber);
    qry.addBindValue(title);
    qry.addBindValue("Przelew");
    qry.addBindValue(amntStr);
    qry.exec();
}

QString transactioninfo::getCurrentDate()
{
    QDate currentDate = QDate::currentDate();
    QString _currentDate = currentDate.toString(Qt::SystemLocaleShortDate);
    return _currentDate;
}
