#include "settingsbd.h"
#include "ui_settingsbd.h"

SettingsBD::SettingsBD(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsBD)
{
    ui->setupUi(this);
    dataForDB = new DataToConnectToDB();

    ui->host    ->setText(QString(dataForDB->hostName));
    ui->port    ->setText(QString(dataForDB->port));
    ui->dbName  ->setText(QString(dataForDB->dbName));
    ui->user    ->setText(QString(dataForDB->login));
    ui->pass    ->setText(QString(dataForDB->pass));
    //Ресайзим вектор значений, по количеству полей необходимых для
    //подключения к БД
    dbData.resize(NUM_DATA_FOR_CONNECT_TO_DB);
    on_buttonBox_accepted();
}

SettingsBD::~SettingsBD()
{
    delete ui;
}

void SettingsBD::on_buttonBox_accepted()
{
    //Добавляем данные в контейнер и передаем в главное окно
    dbData[hostName] = ui->host->text();
    dbData[dbName]   = ui->dbName->text();
    dbData[login]    = ui->user->text();
    dbData[pass]     = ui->pass->text();
    dbData[port]     = ui->port->text();

    emit sig_sendData(dbData);
}




