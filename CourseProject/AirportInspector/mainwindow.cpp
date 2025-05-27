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
    msg  = new QMessageBox(this);
    dataForDB = new DataToConnectToDB();
    workloadDialog = new Workload(nullptr);


    lConnect -> setText(QString("Отсутствует соединение с БД!"));
    lConnect -> setStyleSheet("QLabel { color : red; }");
    ui->statusbar->addPermanentWidget(lConnect,2);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setAlternatingRowColors(true);
    ui->cb_Aeroport->setEnabled(false);
    ui->dateTimeEdit->setEnabled(false);
    ui->pb_flights->setEnabled(false);
    ui->pb_workload->setEnabled(false);

    //Установим размер вектора данных для подключения к БД
    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);

    /*
     * Добавим БД используя стандартный драйвер PSQL и зададим имя.
    */
    dataBase->AddDataBase(POSTGRE_DRIVER, DB_NAME);

    timer->setInterval(5000);
    timer->start();

    connect(settings, &SettingsBD::sig_sendData, this, &MainWindow::slot_ConnectionToDB);
    connect(dataBase, &DataBase::sig_SendStatusConnection, this, &MainWindow::slot_ReceiveStatusConnectionToDB);
    connect(dataBase, &DataBase::sig_SendStatusConnection, workloadDialog, &Workload::slot_status_connection);
    connect(timer, &QTimer::timeout, this, &MainWindow::slot_refresh_connection);


    settings->autoStart();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_ReceiveStatusConnectionToDB(bool status)
{
    connToDB = status;
    settings->setConnectedStatus(connToDB);
    if(connToDB)
    {
        lConnect -> setText(QString("Соединение с БД установлено!"));
        lConnect -> setStyleSheet("QLabel { color : blue; }");
        //timer->stop();
        firstRequest();
        ui->cb_Aeroport->setEnabled(true);
        ui->dateTimeEdit->setEnabled(true);
        ui->pb_flights->setEnabled(true);
        ui->pb_workload->setEnabled(true);
    }
    else
    {
        lConnect -> setText(QString("Отсутствует соединение с БД!"));
        lConnect -> setStyleSheet("QLabel { color : red; }");
        ui->tableView->setModel(NULL);
        ui->cb_Aeroport->setEnabled(false);
        ui->dateTimeEdit->setEnabled(false);
        ui->pb_flights->setEnabled(false);
        ui->pb_workload->setEnabled(false);

        msg->setIcon(QMessageBox::Critical);
        msg->setText(dataBase->getLastError().text());
        msg->exec();
    }

    ui->statusbar->addPermanentWidget(lConnect,1);
}

void MainWindow::slot_ConnectionToDB(QVector<QString> receivData)
{
    dataForConnect = receivData;

    if (!connToDB)
    {
        dataBase->ConnectToDataBase(dataForConnect, POSTGRE_DRIVER, DB_NAME);
    }
    else
    {
        timer->stop();
        dataBase->DisconnectFromDataBase(dataForDB->dbName);
    }
}

void MainWindow::slot_refresh_connection()
{
    if (!connToDB)
    {
        msg->close();
        settings->autoStart();
    }
}

void MainWindow::on_settings_triggered()
{
    settings->changingButton();
    settings->exec();
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
        request = "SELECT flight_no as \"Номер рейса\", scheduled_departure as \"Время вылета\", ad.airport_name->>'ru' as \"Аэропорт \nназначения\" from bookings.flights f "
                  "JOIN bookings.airports_data ad on ad.airport_code = f.arrival_airport "
                  "where f.arrival_airport  = '" + Code + "' "
                           "AND DATE(scheduled_arrival AT TIME ZONE ad.timezone) = to_date('" + dateTimeStr + "', 'DD/MM/YY')";
    }
    else
    {
        request = "SELECT flight_no as \"Номер рейса\", scheduled_departure as \"Время вылета\", ad.airport_name->>'ru' as \"Аэропорт \nотправления\" from bookings.flights f "
                  "JOIN bookings.airports_data ad on ad.airport_code = f.departure_airport "
                  "where f.departure_airport  = '" + Code + "' "
                           "AND DATE(scheduled_departure AT TIME ZONE ad.timezone) = to_date('" + dateTimeStr + "', 'DD/MM/YY')";
    }
    //запрос в БД
    ui->tableView->setModel(dataBase->GetArrivalDeparture(request));
}


void MainWindow::on_pb_workload_clicked()
{
    QString NameCity = ui->cb_Aeroport->currentText();
    QString Code = dataBase->getCode(NameCity);
    workloadDialog->setNameCityStat(NameCity);
    request = "SELECT count(flight_no), "
              "date_trunc('month', scheduled_departure)::date AS Month "
              "FROM bookings.flights f "
              "WHERE (scheduled_departure::date >= DATE('2016-08-15') AND scheduled_departure::date < DATE('2017-09-15')) "
              "AND (departure_airport = '" + Code + "' OR arrival_airport = '" + Code + "') GROUP BY Month";
    workloadDialog->yearRequest(dataBase->GetYearStatistics(request));
    workloadDialog->setIndexMonths();

    request = "SELECT count(flight_no),  date_trunc('day', scheduled_departure)::date AS Day "
              "FROM bookings.flights f "
              "WHERE (scheduled_departure >= DATE('2016-08-15') AND scheduled_departure::date < DATE('2017-09-15')) "
              "AND (departure_airport = '" + Code + "' OR arrival_airport = '" + Code + "') GROUP BY Day";
    workloadDialog->monthsRequest(dataBase->GetMonthsStatistics(request));
    workloadDialog->exec();
}


void MainWindow::on_exit_triggered()
{
    this->close();
}


