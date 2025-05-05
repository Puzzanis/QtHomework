#include "settingsbd.h"
#include "ui_settingsbd.h"

SettingsBD::SettingsBD(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsBD)
{
    ui->setupUi(this);

    ui->host->setPlaceholderText(QString("981757-ca08998.tmweb.ru"));
    ui->port->setPlaceholderText(QString("5432"));
    ui->nameBD->setPlaceholderText(QString("demo"));
    ui->user->setPlaceholderText(QString("netology_usr_cpp"));
    ui->password->setPlaceholderText(QString("CppNeto3"));
}

SettingsBD::~SettingsBD()
{
    delete ui;
}

void SettingsBD::on_buttonBox_accepted()
{
    if (ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        qDebug() << "sjhfkjsh";
    }
}


