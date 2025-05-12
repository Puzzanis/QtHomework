#include "database.h"
#include <qthread.h>

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();

    modelQuery= new QSqlQueryModel(this);
    modelQueryAirports = new QSqlQueryModel(this);
    modelQueryFlights = new QSqlQueryModel(this);
    modelQueryYear = new QSqlQueryModel(this);
    modelQueryMonths = new QSqlQueryModel(this);

    dataBase->setConnectOptions("connect_timeout=5");
}

DataBase::~DataBase()
{
    delete dataBase;
}
/*!
* \brief Метод добавляет БД к экземпляру класса QSqlDataBase
* \param driver драйвер БД
* \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
*/
void DataBase::AddDataBase(QString driver, QString nameDB)
{
    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);
}
/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data, QString driver, QString nameDB)
{
    if (dataBase->driverName().isEmpty())
    {
        AddDataBase("QPSQL", "demo");
    }
    isConnect = dataBase->isOpen();

    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());
    bool op = dataBase->open();
    emit sig_SendStatusConnection(op);
    qDebug() << dataBase->driverName();
}

/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{
    isConnect = dataBase->isOpen();
    if (isConnect)
    {
        *dataBase = QSqlDatabase::database(nameDb);
        dataBase->close();
        isConnect = dataBase->isOpen();
        emit sig_SendStatusConnection(isConnect);
    }
}

QSqlQueryModel * DataBase::GetAirports(QString request)
{
    modelQueryAirports->setQuery(QSqlQuery(request, *dataBase));
    if (modelQueryAirports->lastError().isValid()) {
        qDebug() << "Ошибка в запросе: " << modelQueryAirports->lastError().text();
    }
    else
    {
        qDebug() << "Запрос выполнен успешно";
    }

    int size = modelQueryAirports->rowCount();
    while(size--)
    {
        QSqlRecord record = modelQueryAirports->record(size);
        QVariant NameCity;
        QVariant Code;
        for (int i = 0; i < record.count(); ++i)
        {
            if(i == 0){
                NameCity = record.value(i);
            }
            else
            {
                Code = record.value(i);
            }
        }
        mapCityAndCode.insert(NameCity.toString(),Code.toString());
    }
    return modelQueryAirports;
}

QSqlQueryModel *DataBase::GetArrivalDeparture(QString request)
{
    modelQueryFlights->setQuery(QSqlQuery(request, *dataBase));
    if (modelQueryFlights->lastError().isValid())
    {
        qDebug() << "Ошибка в запросе: " << modelQueryFlights->lastError().text();
    } else
    {
        qDebug() << "Запрос выполнен успешно";

    }
    return modelQueryFlights;
}

QSqlQueryModel *DataBase::GetYearStatistics(QString request)
{
    modelQueryYear->setQuery(QSqlQuery(request, *dataBase));
    if ( modelQueryYear->lastError().isValid()) {
        qDebug() << "Ошибка в запросе: " << modelQueryYear->lastError().text();
    }
    else
    {
        qDebug() << "Запрос выполнен успешно";

    }
    return modelQueryYear;
}

QSqlQueryModel *DataBase::GetMonthsStatistics(QString request)
{
    modelQueryMonths->setQuery(QSqlQuery(request, *dataBase));
    if (modelQueryMonths->lastError().isValid())
    {
        qDebug() << "Ошибка в запросе: " << modelQueryMonths->lastError().text();
    }
    else
    {
        qDebug() << "Запрос выполнен успешно"  << Qt::endl;
    }

    return modelQueryMonths;
}


/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::getLastError()
{
    return dataBase->lastError();
}

QString  DataBase::getCode(QString city)
{
    return mapCityAndCode[city];
}
