#include "database.h"

bool database::connection_open()
{
    mydb =QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/Damian/Desktop/project/customers.sqlite");

    if(!mydb.open())
    {
        //qDebug()<<("FAILED TO OPEN DB");
        return false;
    }
    else
    {
        //qDebug()<<("CONNECTED");
        return true;
    }
}

void database::connection_close()
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}
