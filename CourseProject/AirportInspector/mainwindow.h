#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTimer>
#include <qlabel.h>
#include "database.h"
#include "settingsbd.h"
#include "structures.h"
#include "workload.h"

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

signals:
    void sig_RequestToDb(QString request);


private slots:
    void on_action_triggered();
    void on_pb_clear_clicked();
    void on_pb_flights_clicked();
    void on_pb_workload_clicked();
    void slot_refresh_connection();
    void slot_ReceiveStatusConnectionToDB(bool status);
    void slot_ConnectionToDB(QVector<QString> receivData);

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void firstRequest();

private:
    QVector<QString> dataForConnect; //Данные для подключения к БД.

    Ui::MainWindow *ui;
    SettingsBD *settings;
    QLabel* lConnect;

    DataBase* dataBase;
    DataToConnectToDB* dataForDB;

    Workload * workloadDialog;
    QMessageBox* msg;

    QTimer* timer;

    QString request;
    bool connToDB{false};

};
#endif // MAINWINDOW_H
