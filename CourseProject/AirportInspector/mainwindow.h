#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <qlabel.h>
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

private slots:
    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    SettingsBD *settings;
    QLabel* lDateTime;
    QTimer* timer;
    QDateTime* dt;

private:
    void time_update();
};
#endif // MAINWINDOW_H
