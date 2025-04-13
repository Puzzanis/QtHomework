#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    this->setWindowTitle("Stopwatch");
    ui->label->setText(QString::number(0));
    ui->label->setFont(QFont("Times", 45, QFont::Bold));
    ui->btnStartStop->setText("Старт");
    ui->btnClear->setText("Очистить");
    ui->btnCircle->setText("Круг");
    ui->btnCircle->setEnabled(false);


    stopwtch = new Stopwatch(this);
    QObject::connect(stopwtch, &Stopwatch::sig_ChangeStateButton, this, &MainWindow::changeStateBtn);
    QObject::connect(stopwtch, &Stopwatch::sig_setText, this, &MainWindow::sendToTextBr);
    QObject::connect(stopwtch, &Stopwatch::sig_clearText, this, &MainWindow::clearText);
    QObject::connect(stopwtch, &Stopwatch::sig_Time, this, &MainWindow::Time);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendToTextBr(QString str)
{
    ui->textBrowser->append(str);
}

void MainWindow::changeStateBtn(QString state)
{
    ui->btnCircle->setEnabled((state=="Стоп")?true:false);
    ui->btnStartStop->setText(state);
}

void MainWindow::clearText(int num)
{
    ui->textBrowser->clear();
    ui->label->setText(QString::number(num));
}

void MainWindow::Time(int num)
{
    ui->label->setText(QString::number(num));
}

void MainWindow::on_btnStartStop_clicked()
{
    QString state = ui->btnStartStop->text();
    stopwtch->ChangeStateButton(state);
}


void MainWindow::on_btnCircle_clicked()
{
    stopwtch->setText();
}


void MainWindow::on_btnClear_clicked()
{
    stopwtch->clearText();
}

