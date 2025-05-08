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
    void autoStart();
    void setConnectedStatus(const bool con);
    void changingButton();

signals:
    void sig_sendData(QVector<QString> dbData);

private slots:
    void on_pb_connect_clicked();

private:
    QVector<QString> dbData; //Данные для подключения к БД.
    DataToConnectToDB* dataForDB;
    Ui::SettingsBD *ui;

    bool connToDB{false};
};

#endif // SETTINGSBD_H
