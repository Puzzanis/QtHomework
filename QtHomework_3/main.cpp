#include <QCoreApplication>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QTcpServer>
#include <QTcpSocket>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Messages_dev");
    db.setUserName("postgres");
    db.setPassword("root");
    bool ok = db.open();
    qDebug() << ok;

    QSqlQuery query;
    query.exec("SELECT * FROM users");

    while (query.next())
    {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        qDebug() << id << name;
    }

    QTcpServer * mTcpServer = new QTcpServer();
    QTcpSocket * mTcpSocket = mTcpServer->nextPendingConnection();
    //mTcpSocket->write("Hello, World!!! I am echo server!\r\n");


    mTcpSocket->close();



    return a.exec();
}
