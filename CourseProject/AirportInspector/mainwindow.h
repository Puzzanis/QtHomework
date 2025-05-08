#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtConcurrent>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTimer>
#include <qlabel.h>
#include "database.h"
#include "settingsbd.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ReceiveStatusConnectionToDB(bool status);
    void ConnectionToDB(QVector<QString> receivData);
    void Refresh_connection();

signals:
    void sig_RequestToDb(QString request);


private slots:
    void on_action_triggered();

    void on_pb_clear_clicked();

    void on_pb_flights_clicked();

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void firstRequest();

private:
    QVector<QString> dataForConnect; //Данные для подключения к БД.

    Ui::MainWindow *ui;
    SettingsBD *settings;
    QLabel* lConnect;

    DataBase* dataBase;
    QMessageBox* msg;

    QTimer* timer;

    QString request;

};
#endif // MAINWINDOW_H
