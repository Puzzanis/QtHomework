#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //pushButton init
    ui->toggle->setText("Кнопка");
    ui->toggle->setCheckable(true);
    ui->toggle->setStyleSheet("QPushButton {background-color: green; border-style:inset;}");

    //progressBar init
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(10);
    ui->progressBar->setValue(0);

    //radioButton init
    ui->radioButton->setText("Элемент 1");
    ui->radioButton->setChecked(true);

    //radioButton_2 init
    ui->radioButton_2->setText("Элемент 2");

    //comboBox init
    ui->comboBox->addItem("First");
    ui->comboBox->addItem("Second");
    ui->comboBox->addItem("Third");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_toggle_toggled(bool checked)
{
    progress = (progress>9)?0:++progress;
    ui->progressBar->setValue(progress);
    if (checked)
    {
        ui->toggle->setStyleSheet("QPushButton {background-color: red; border-style:inset;}");
    }
    else
    {
        ui->toggle->setStyleSheet("QPushButton {background-color: green; border-style:inset;}");
    }
}

