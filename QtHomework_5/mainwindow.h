#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QString>
#include <QDebug>
#include <QtGui>

#include "stopwatch.h"

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
    void sendToTextBr(QString str);
    void changeStateBtn(QString state);
    void clearText(int num);
    void Time(int num);

private slots:
    void on_btnStartStop_clicked();

    void on_btnCircle_clicked();

    void on_btnClear_clicked();

private:
    Ui::MainWindow *ui;
    Stopwatch* stopwtch;
};
#endif // MAINWINDOW_H
