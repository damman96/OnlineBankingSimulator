#include "transactioninfo.h"
#include "widget.h"

transactioninfo::transactioninfo()
{

}

bool transactioninfo::checkAccountBalance(double balance, double amount)
{
    if(balance >= amount)
        return true;
    else return false;
}

bool transactioninfo::checkAmount(QString amount)
{
    int lngth = amount.length();
    if(lngth <= 7)
    {
        for(int i=0; i< amount.length(); i++)
        {
            if(amount[i]=="0" || amount[i]=="1" || amount[i]=="2" || amount[i]=="3" || amount[i]=="4" || amount[i]=="5" || amount[i]=="6"
                                            || amount[i]=="7" || amount[i]=="8" || amount[i]=="9" || amount[i]=="0" || amount[i]=="0" || amount[i] ==".")
                            return true;

        }
    }
    else return false;
}

bool transactioninfo::checkRecipient(QString recipient)
{
    if(recipient!="")
        return true;
    else return false;
}

bool transactioninfo::checkTitle(QString title)
{
    if(title!="")
        return true;
    else return false;
}

bool transactioninfo::checkAccNumber(QString accNumber)
{
    int lngth = accNumber.length();

    if(lngth == 32)
    {
        for(int i=0; i< accNumber.length(); i++)
        {
            if(accNumber[i]=="0" || accNumber[i]=="1" || accNumber[i]=="2" || accNumber[i]=="3" || accNumber[i]=="4" || accNumber[i]=="5" || accNumber[i]=="6"
                                            || accNumber[i]=="7" || accNumber[i]=="8" || accNumber[i]=="9" || accNumber[i]=="0" || accNumber[i]=="0" || accNumber[i] ==" ")
                            return true;

        }
    }
    else return false;
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

void transactioninfo::getSenderData(QString senderName, QString senderUsername, QString senderSurname, QString senderAccNumber, double senderBalance, int senderTransactions, int senderOperations)
{
    _senderName = senderName;
    _senderUsername = senderUsername;
    _senderSurname = senderSurname;
    _senderAccNumber = senderAccNumber;
    _senderBalance = senderBalance;
    _senderTransactions = senderTransactions;
    _senderOperations = senderOperations;

}

void transactioninfo::updateTransactions(QString Username, double amount)
{
    _senderTransactions+=amount;
    QString transactionsString = QString::number(_senderTransactions);
    QSqlQuery qry;
    qry.exec("UPDATE customers SET TRANSACTIONS='"+transactionsString+"' WHERE USERNAME='"+Username+"'");

}

void transactioninfo::updateOperations(QString Username)
{
    _senderOperations+=1;
    QString operationsString = QString::number(_senderOperations);
    QSqlQuery qry;
    qry.exec("UPDATE customers SET OPERATIONS='"+operationsString+"' WHERE USERNAME='"+Username+"'");
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
    QString currDate;

    int day = currentDate.day();
    int month = currentDate.month();
    int year = currentDate.year();

    QString dayStr = QString::number(day);
    QString monthStr = QString::number(month);
    QString yearStr = QString::number(year);

    currDate = yearStr + "-" + monthStr + "-" + dayStr;

    return currDate;
}
