#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QString>

#define POSTGRE_DRIVER "QPSQL"
#define DB_NAME "MyDB"

//Количество полей данных необходимых для подключения к БД
#define NUM_DATA_FOR_CONNECT_TO_DB 5

//Перечисление полей данных
enum fieldsForConnect{
    hostName = 0,
    dbName = 1,
    login = 2,
    pass = 3,
    port = 4
};

struct DataToConnectToDB
{
    QString hostName{"981757-ca08998.tmweb.ru"};
    QString dbName{"demo"};
    QString login{"netology_usr_cpp"};
    QString pass{"CppNeto3"};
    QString port{"5432"};
};

#endif // STRUCTURES_H
