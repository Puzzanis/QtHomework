#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new SettingsBD(this);
    dataBase = new DataBase(this);
    lConnect = new QLabel(this);
    timer = new QTimer(this);


    lConnect -> setText(QString("Отсутствует соединение с БД!"));
    lConnect -> setStyleSheet("QLabel { color : red; }");
    ui->statusbar->addPermanentWidget(lConnect,2);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setAlternatingRowColors(true);

    //Установим размер вектора данных для подключения к БД
    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);

    /*
     * Добавим БД используя стандартный драйвер PSQL и зададим имя.
    */
    dataBase->AddDataBase(POSTGRE_DRIVER, DB_NAME);

    connect(settings, &SettingsBD::sig_sendData, this, &MainWindow::ConnectionToDB);
    connect(dataBase, &DataBase::sig_SendStatusConnection, this, &MainWindow::ReceiveStatusConnectionToDB);
    connect(timer, &QTimer::timeout, this, &MainWindow::Refresh_connection);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReceiveStatusConnectionToDB(bool status)
{
    if(status)
    {
        lConnect -> setText(QString("Соединение с БД установлено!"));
        lConnect -> setStyleSheet("QLabel { color : blue; }");
        timer->stop();
        firstRequest();
    }
    else
    {
        timer->start(5000);
        lConnect -> setText(QString("Отсутствует соединение с БД!"));
        lConnect -> setStyleSheet("QLabel { color : red; }");

        dataBase->DisconnectFromDataBase(DB_NAME);
        msg->setIcon(QMessageBox::Critical);
        msg->setText(dataBase->GetLastError().text());
        msg->show();
    }

    ui->statusbar->addPermanentWidget(lConnect,1);
}

void MainWindow::ConnectionToDB(QVector<QString> receivData)
{
    dataForConnect = receivData;
    dataBase->ConnectToDataBase(dataForConnect);
}

void MainWindow::Refresh_connection()
{
    msg->close();
}

void MainWindow::on_action_triggered()
{
    settings->show();
}

void MainWindow::firstRequest()
{
    request = "SELECT airport_name->>'ru' as airportName, airport_code FROM bookings.airports_data";
    ui->cb_Aeroport->setModel(dataBase->GetAirports(request));
}

void MainWindow::on_pb_clear_clicked()
{
    ui->tableView->setModel(NULL);
}

void MainWindow::on_pb_flights_clicked()
{
    QString NameCity = ui->cb_Aeroport->currentText();
    QString Code = dataBase->getCode(NameCity);
    QString dateTimeStr = ui->dateTimeEdit->text();
    if (ui->rb_arrival->isChecked())
    {
        request = "SELECT flight_no as \"Номер рейса\", scheduled_arrival as \"Время прилета\", ad.airport_name->>'ru' as \"Аэропорт\" from bookings.flights f "
                  "JOIN bookings.airports_data ad on ad.airport_code = f.departure_airport "
                  "where f.arrival_airport  = '" + Code + "' "
                           "AND DATE(scheduled_arrival AT TIME ZONE ad.timezone) = to_date('" + dateTimeStr + "', 'DD/MM/YY')";
    }
    else
    {
        request = "SELECT flight_no as \"Номер рейса\", scheduled_departure as \"Время вылета\", ad.airport_name->>'ru' as \"Аэропорт\" from bookings.flights f "
                  "JOIN bookings.airports_data ad on ad.airport_code = f.departure_airport "
                  "where f.departure_airport  = '" + Code + "' "
                           "AND DATE(scheduled_departure AT TIME ZONE ad.timezone) = to_date('" + dateTimeStr + "', 'DD/MM/YY')";
    }
    //запрос в БД
    qDebug() << request;
    ui->tableView->setModel(dataBase->GetArrivalDeparture(request));
}

