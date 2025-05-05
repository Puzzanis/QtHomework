#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = new SettingsBD(this);
    lDateTime = new QLabel(this);
    dt = new QDateTime();
    timer = new QTimer(this);


    connect(timer, &QTimer::timeout, this, &MainWindow::time_update);
    timer->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    settings->show();
}

void MainWindow::time_update()
{
    lDateTime->setText(dt->currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

    ui->statusbar->addPermanentWidget(lDateTime);
}

