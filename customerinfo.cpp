#include "customerinfo.h"
#include "widget.h"

customerInfo::customerInfo()
{   

}

int customerInfo::dataLogin(QString username, QString password)
{
    QSqlQuery qry;

    if(qry.exec("SELECT USERNAME, PASSWORD, NAME, SURNAME, BALANCE, TRANSACTIONS_LIMIT, ACCOUNT_NUMBER, OPERATIONS_LIMIT, CREDIT, NOWL FROM customers WHERE USERNAME='"+username+"' AND PASSWORD='"+password+"'"))
    {
        if(qry.next())
        {                            
            _username = qry.value(0).toString();
            _name = qry.value(2).toString();
            _surname = qry.value(3).toString();
            _balance = qry.value(4).toDouble();
            _transactionsLimit = qry.value(5).toInt();
            _accountNumber = qry.value(6).toString();
            _operationsLimit = qry.value(7).toInt();
            _credit = qry.value(8).toInt();
            _nowl = qry.value(9).toInt();

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

bool customerInfo::changePassword(QString password,QString oldPassword,QString newPassword)
{
    if(oldPassword==password)
    {
        QSqlQuery qry;
        qry.exec("UPDATE customers SET PASSWORD = '"+newPassword+"' WHERE PASSWORD = '"+password+"'");
        return true;
    }
    else return false;
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

int customerInfo::getTransactionsLimit()
{
    return _transactionsLimit;
}

int customerInfo::getOperationsLimit()
{
    return _operationsLimit;
}

int customerInfo::getCredit()
{
    return _credit;
}
