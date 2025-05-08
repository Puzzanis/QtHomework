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

}

SettingsBD::~SettingsBD()
{
    delete ui;
}

void SettingsBD::autoStart()
{
    dbData[hostName] = ui->host->text();
    dbData[dbName]   = ui->dbName->text();
    dbData[login]    = ui->user->text();
    dbData[pass]     = ui->pass->text();
    dbData[port]     = ui->port->text();

    emit sig_sendData(dbData);
}

void SettingsBD::setConnectedStatus(const bool con)
{
    connToDB = con;
}

void SettingsBD::changingButton()
{
    ui->pb_connect->setText((connToDB)?"Отключиться":"Подключиться");
}

void SettingsBD::on_pb_connect_clicked()
{

    dbData[hostName] = ui->host->text();
    dbData[dbName]   = ui->dbName->text();
    dbData[login]    = ui->user->text();
    dbData[pass]     = ui->pass->text();
    dbData[port]     = ui->port->text();

    emit sig_sendData(dbData);
    this->close();
}


