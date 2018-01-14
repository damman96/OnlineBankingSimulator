#include "customerinfo.h"
#include "widget.h"

customerInfo::customerInfo()
{   

}

int customerInfo::getLoginData(QString username, QString password)
{
    QSqlQuery qry;

    if(qry.exec("SELECT USERNAME, NOWL FROM customers WHERE USERNAME='"+username+"' AND PASSWORD='"+password+"'"))
    {
        if(qry.next())
        {                            
            _username = qry.value(0).toString();
            _nowl = qry.value(1).toInt();

            if(_nowl < defNOWL)
                return 0;
            else
                return 1;
        }
        else
        {
            QSqlQuery qry;
            qry.exec("SELECT NOWL FROM customers WHERE USERNAME='"+username+"'");
            if(qry.next())
            {
                _nowl = qry.value(0).toInt();
                if(_nowl < defNOWL)
                {
                _nowl++;
                QString _nowlString = QString::number(_nowl);
                qry.exec("UPDATE customers SET NOWL='"+_nowlString+"' WHERE USERNAME='"+username+"'");
                }
                else return 1;
            }
            return -1;
        }
    }
}

void customerInfo::getPersonalInformation(QString username)
{
    QSqlQuery qry;
    qry.exec("SELECT NAME, SURNAME, BALANCE, TRANSACTIONS_LIMIT, ACCOUNT_NUMBER, OPERATIONS_LIMIT, CREDIT, TRANSACTIONS, OPERATIONS, LASTLOGIN FROM customers WHERE USERNAME='"+username+"'");
    if(qry.next())
    {
        _name = qry.value(0).toString();
        _surname = qry.value(1).toString();
        _balance = qry.value(2).toDouble();
        _transactionsLimit = qry.value(3).toInt();
        _accountNumber = qry.value(4).toString();
        _operationsLimit = qry.value(5).toInt();
        _credit = qry.value(6).toInt();
        _transactions = qry.value(7).toDouble();
        _operations = qry.value(8).toInt();
        _lastLoginDate = qry.value(9).toString();
    }

}

bool customerInfo::changePassword(QString password,QString oldPassword,QString newPassword)
{
    if(oldPassword==password && _operations < _operationsLimit)
    {
        _operations+=1;
        QString operString = QString::number(_operations);
        QSqlQuery qry;
        qry.exec("UPDATE customers SET PASSWORD = '"+newPassword+"', OPERATIONS = '"+operString+"' WHERE PASSWORD = '"+password+"'");
        return true;
    }
    else return false;
}

bool customerInfo::changeTransactionsLimit(QString username, QString oldLimit, QString newLimit)
{
    if(oldLimit!=newLimit && newLimit!="0" && _operations < _operationsLimit)
    {
        _operations+=1;
        QString operString = QString::number(_operations);
        QSqlQuery qry;
        qry.exec("UPDATE customers SET TRANSACTIONS_LIMIT = '"+newLimit+"', OPERATIONS = '"+operString+"' WHERE USERNAME = '"+username+"'");
        return true;
    }
    else return false;
}

bool customerInfo::changeOperationsLimit(QString username, QString oldLimit, QString newLimit)
{
    if(oldLimit!=newLimit && newLimit!="0" && _operations < _operationsLimit)
    {
        _operations+=1;
        QString operString = QString::number(_operations);
        QSqlQuery qry;
        qry.exec("UPDATE customers SET OPERATIONS_LIMIT = '"+newLimit+"', OPERATIONS = '"+operString+"' WHERE USERNAME = '"+username+"'");
        return true;
    }
    else return false;
}

QString customerInfo::getCurrentDate()
{
    QDate currentDate = QDate::currentDate();
    QString currDate = currentDate.toString(Qt::DefaultLocaleShortDate);

    QTime currentTime = QTime::currentTime();
    QString currTime = currentTime.toString("hh:mm:ss");
    loginDate = currDate + " o godz. " + currTime;
    return loginDate;
}

void customerInfo::udpatelastLoginDate(QString username)
{
    QSqlQuery qry;
    qry.exec("UPDATE customers SET LASTLOGIN = '"+loginDate+"' WHERE USERNAME = '"+username+"'");
}

QString customerInfo::getUsername()
{
    return _username;
}

QString customerInfo::getName()
{
    return _name;
}

QString customerInfo::getSurname()
{
    return _surname;
}

double customerInfo::getBalance()
{
    return _balance;
}

QString customerInfo::getAccountNumber()
{
    return _accountNumber;
}

double customerInfo::getTransactionsLimit()
{
    return _transactionsLimit;
}

double customerInfo::getTransactions()
{
    return _transactions;
}

int customerInfo::getOperationsLimit()
{
    return _operationsLimit;
}

int customerInfo::getOperations()
{
    return _operations;
}

int customerInfo::getCredit()
{
    return _credit;
}

QString customerInfo:: getLastLoginDate()
{
    return _lastLoginDate;
}
