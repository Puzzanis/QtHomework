#ifndef SETTINGSBD_H
#define SETTINGSBD_H

#include <QDialog>

namespace Ui {
class SettingsBD;
}

class SettingsBD : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsBD(QWidget *parent = nullptr);
    ~SettingsBD();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SettingsBD *ui;
};

#endif // SETTINGSBD_H
