#include "database.h"

bool database::connection_open()
{
    mydb =QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/Damian/Desktop/OnlineBankingSimulator/customers.sqlite");

    if(!mydb.open())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void database::connection_close()
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}
