#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();

    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    connect(udpWorker, &UDPworker::sig_sendTextToGUI, this, &MainWindow::DisplayText);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << dateTime;

        udpWorker->SendDatagram(dataToSend);
        timer->start(TIMER_DELAY);

    });



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_start_clicked()
{
    timer->start(TIMER_DELAY);
}


void MainWindow::DisplayTime(QDateTime data)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));


}

void MainWindow::DisplayText(QString data, QHostAddress address)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Принято сообщение \"" + data + "\" от " + address.toString() +
                          ", размер сообщения(байт) " + QString::number(data.size()) + ". " +
                          "Принято пакетов " + QString::number(counterPck));
}


void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}


void MainWindow::on_pushButton_clicked()
{
    QByteArray dataToSend;
    QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

    outStr << ui->lineEdit->text();

    udpWorker->SendTextDatagram(dataToSend);
}

