#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    this->setWindowTitle("Stopwatch");
    ui->label->setText(QString(".000"));
    ui->label_2->setText(QString("00"));
    ui->label_3->setText(QString("00:"));
    ui->label->setFont(QFont("Times", 40, QFont::Bold));
    ui->label_2->setFont(QFont("Times", 40, QFont::Bold));
    ui->label_3->setFont(QFont("Times", 40, QFont::Bold));
    ui->btnStartStop->setText("Старт");
    ui->btnClear->setText("Очистить");
    ui->btnCircle->setText("Круг");
    ui->btnCircle->setEnabled(false);


    stopwtch = new Stopwatch(this);
    QObject::connect(stopwtch, &Stopwatch::sig_Time, this, &MainWindow::Time);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Time(QString m, QString s, QString ms)
{
    ui->label->setText(ms);
    ui->label_2->setText(s);
    ui->label_3->setText(m);
}



void MainWindow::on_btnCircle_clicked()
{
    QString str = stopwtch->setText();
    ui->textBrowser->append(str);
}


void MainWindow::on_btnClear_clicked()
{
    ui->textBrowser->clear();
    stopwtch->clearText();
    ui->label_3->setText(QString("00:"));
    ui->label_2->setText(QString("00"));
    ui->label->setText(QString(".000"));
}


void MainWindow::on_btnStartStop_clicked()
{
    QString state;
    state = ui->btnStartStop->text();
    ui->btnStartStop->setText((state == "Старт")?"Стоп":"Старт");

    state = ui->btnStartStop->text();
    ui->btnCircle->setEnabled((state=="Стоп")?true:false);
    stopwtch->ChangeStateButton(state);
}

