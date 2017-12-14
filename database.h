#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class database
{
public:
    bool connection_open();
    void connection_close();
		
private:
    QSqlDatabase mydb;
};

#endif // DATABASE_H
