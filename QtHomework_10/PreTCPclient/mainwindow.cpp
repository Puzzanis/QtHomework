#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    client = new TCPclient(this);
    //Доступность полей по умолчанию
    ui->le_data->setEnabled(false);
    ui->pb_request->setEnabled(false);
    ui->lb_connectStatus->setText("Отключено");
    ui->lb_connectStatus->setStyleSheet("color: red");

    //При отключении меняем надписи и доступность полей.
    connect(client, &TCPclient::sig_Disconnected, this, [&]{

        ui->lb_connectStatus->setText("Отключено");
        ui->lb_connectStatus->setStyleSheet("color: red");
        ui->pb_connect->setText("Подключиться");
        ui->le_data->setEnabled(false);
        ui->pb_request->setEnabled(false);
        ui->spB_port->setEnabled(true);
        ui->spB_ip1->setEnabled(true);
        ui->spB_ip2->setEnabled(true);
        ui->spB_ip3->setEnabled(true);
        ui->spB_ip4->setEnabled(true);

    });



 /*
  * Соединяем сигналы со слотами
 */
    connect(client, &TCPclient::sig_connectStatus, this, &MainWindow::DisplayConnectStatus);

    connect(client, &TCPclient::sig_Success, this, &MainWindow::DisplaySuccess);
    connect(client, &TCPclient::sig_Error, this, &MainWindow::DisplayError);
    connect(client, &TCPclient::sig_sendTime, this, &MainWindow::DisplayTime);
    connect(client, &TCPclient::sig_sendFreeSize, this, &MainWindow::DisplayFreeSpace);
    connect(client, &TCPclient::sig_sendStat, this, &MainWindow::DisplayStat);
    connect(client, &TCPclient::sig_SendReplyForSetData, this, &MainWindow::SetDataReply);
    connect(client, &TCPclient::sig_ClearBuffer, this, &MainWindow::ClearBuffer);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief Группа методо отображения различных данных
 */
void MainWindow::DisplayTime(QDateTime time)
{
    ui->tb_result->append("Время на сервере: " + time.toString());
}
void MainWindow::DisplayFreeSpace(uint32_t freeSpace)
{
    ui->tb_result->append("Свободного места на сервере осталось: " + QString::number(freeSpace));
}
void MainWindow::SetDataReply(QString replyString)
{
    ui->tb_result->append("Отправленое сообщенное: " + replyString);
}
void MainWindow::DisplayStat(StatServer stat)
{
    ui->tb_result->append("======== Статистика =========");
    ui->tb_result->append("Принято: " + QString::number(stat.incBytes) + " байт");
    ui->tb_result->append("Передано: " + QString::number(stat.sendBytes) + " байт");
    ui->tb_result->append("Принто пакетов: " + QString::number(stat.sendPck));
    ui->tb_result->append("Передано пакетов: " + QString::number(stat.revPck));
    ui->tb_result->append("Время работы сервера: " + QString::number(stat.workTime));
    ui->tb_result->append("Количество подключенных клиентов: " + QString::number(stat.clients));
     ui->tb_result->append("==========================");
}
void MainWindow::DisplayError(uint16_t error)
{
    switch (error) {
    case ERR_NO_FREE_SPACE:
        ui->tb_result->append("Недостаточно свободного места");
        break;
    case ERR_ZERO_LEN:
        ui->tb_result->append("Передано пустое сообщение");
        break;
    case ERR_NO_FUNCT:
    case ERR_SEND_DATA_TO_SERVER:
        ui->tb_result->append("Ошибка отправки данных на сервер!!!");
        break;
    default:
        break;
    }
}
/*!
 * \brief Метод отображает квитанцию об успешно выполненном сообщениии
 * \param typeMess ИД успешно выполненного сообщения
 */
void MainWindow::DisplaySuccess(uint16_t typeMess)
{
    QString str;
    switch (typeMess) {
    case GET_TIME:
        str = "--> Запрос времени сервера...";
        break;
    case GET_SIZE:
        str = "--> Запрос свободного места на сервере...";
        break;
    case GET_STAT:
        str = "--> Запрос статистики от сервера...";
        break;
    case SET_DATA:
        str = "Отправка сообщения на сервер...";
        break;
    case CLEAR_DATA:
        str = "Освободить место на сервере...";
        break;
    default:
        break;
    }
    ui->tb_result->append(str);
}

void MainWindow::ClearBuffer(QString msg)
{
    ui->tb_result->append(msg);
}

/*!
 * \brief Метод отображает статус подключения
 */
void MainWindow::DisplayConnectStatus(uint16_t status)
{

    if(status == ERR_CONNECT_TO_HOST){

        ui->tb_result->append("Ошибка подключения к порту: " + QString::number(ui->spB_port->value()));

    }
    else{
        ui->lb_connectStatus->setText("Подключено");
        ui->lb_connectStatus->setStyleSheet("color: green");
        ui->pb_connect->setText("Отключиться");
        ui->spB_port->setEnabled(false);
        ui->pb_request->setEnabled(true);
        ui->spB_ip1->setEnabled(false);
        ui->spB_ip2->setEnabled(false);
        ui->spB_ip3->setEnabled(false);
        ui->spB_ip4->setEnabled(false);
    }

}

/*!
 * \brief Обработчик кнопки подключения/отключения
 */
void MainWindow::on_pb_connect_clicked()
{
    if(ui->pb_connect->text() == "Подключиться"){

        uint16_t port = ui->spB_port->value();

        QString ip = ui->spB_ip4->text() + "." +
                     ui->spB_ip3->text() + "." +
                     ui->spB_ip2->text() + "." +
                     ui->spB_ip1->text();

        client->ConnectToHost(QHostAddress(ip), port);

    }
    else{

        client->DisconnectFromHost();
    }
}

/*
 * Для отправки сообщения согласно ПИВ необходимо
 * заполнить заголовок и передать его на сервер. В ответ
 * сервер вернет информацию в соответствии с типом сообщения
*/
void MainWindow::on_pb_request_clicked()
{

    ServiceHeader header;
    QString msg = "";
    header.id = ID;
    header.status = STATUS_SUCCES;
    header.len = 0;

    switch (ui->cb_request->currentIndex()){

       //Получить время
       case 0:
           header.idData = GET_TIME;
           break;
       //Получить свободное место
       case 1:
           header.idData = GET_SIZE;
           break;
       //Получить статистику
       case 2:
            header.idData = GET_STAT;
            break;
       //Отправить данные
       case 3:
           header.idData = SET_DATA;
           msg = ui->le_data->text();
           header.len = msg.toUtf8().size();
           ui->le_data->clear();
           break;
       //Очистить память на сервере
       case 4:
           header.idData = CLEAR_DATA;
           break;
       default:
            ui->tb_result->append("Такой запрос не реализован в текущей версии");
       return;

   }
       if (msg.isEmpty())
       {
           client->SendRequest(header);
       }
       else
       {
           client->SendData(header, msg);
       }
}

/*!
 * \brief Обработчик изменения индекса запроса
 */
void MainWindow::on_cb_request_currentIndexChanged(int index)
{
    //Разблокируем поле отправления данных только когда выбрано "Отправить данные"
    if(ui->cb_request->currentIndex() == 3){
        ui->le_data->setEnabled(true);
    }
    else{
        ui->le_data->setEnabled(false);
    }
}

