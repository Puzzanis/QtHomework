#ifndef SETTINGSBD_H
#define SETTINGSBD_H

#include <QDialog>
#include "structures.h"


namespace Ui {
class SettingsBD;
}

class SettingsBD : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsBD(QWidget *parent = nullptr);
    ~SettingsBD();

signals:
    void sig_sendData(QVector<QString> dbData);

private slots:
    void on_buttonBox_accepted();


private:
    QVector<QString> dbData; //Данные для подключения к БД.
    DataToConnectToDB* dataForDB;
    Ui::SettingsBD *ui;
};

#endif // SETTINGSBD_H
