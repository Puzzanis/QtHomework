#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/qsqldatabase.h>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMap>
#include <QThread>
#include "structures.h"

class DataBase: public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    QSqlError getLastError(void);

    void AddDataBase(QString driver, QString nameDB = "");
    void ConnectToDataBase(QVector<QString> dataForConnect, QString driver, QString nameDB);
    void DisconnectFromDataBase(QString nameDb = "");
    void RequestToDB(QString request);
    QSqlQueryModel * GetAirports(QString request);
    QSqlQueryModel * GetArrivalDeparture(QString request);
    QSqlQueryModel * GetYearStatistics(QString request);
    QSqlQueryModel * GetMonthsStatistics(QString request);
    QString getCode(QString city);

signals:

    void sig_SendQueryFromDB(QSqlQueryModel *model);
    void sig_SendTableFromDB(QSqlTableModel *model);
    void sig_SendStatusConnection(bool);

private:
    QMap<QString, QString>  mapCityAndCode;
    QSqlDatabase* dataBase;
    QSqlQueryModel* modelQuery;
    QSqlQueryModel * modelQueryAirports = nullptr;
    QSqlQueryModel * modelQueryFlights = nullptr;
    QSqlQueryModel * modelQueryYear = nullptr;
    QSqlQueryModel * modelQueryMonths = nullptr;

    bool isConnect{false};

};

#endif // DATABASE_H
