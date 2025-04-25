#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent)
{



}


/*!
 * @brief Метод инициализирует UDP сервер
 */
void UDPworker::InitSocket()
{

    serviceUdpSocket = new QUdpSocket(this);
    serviceUdpSocket2 = new QUdpSocket(this);
    /*
     * Соединяем присваиваем адрес и порт серверу и соединяем функцию
     * обраотчик принятых пакетов с сокетом
     */
    serviceUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT);
    serviceUdpSocket2->bind(QHostAddress::LocalHost, BIND_PORT_1);

    connect(serviceUdpSocket, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagrams);
    connect(serviceUdpSocket2, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagrams2);

}

/*!
 * @brief Метод осуществляет обработку принятой датаграммы
 */
void UDPworker::ReadDatagram(QNetworkDatagram datagram)
{

    QByteArray data;
    data = datagram.data();
    port = datagram.destinationPort();
    address = datagram.destinationAddress();

    QDataStream inStr(&data, QIODevice::ReadOnly);

    if (port == BIND_PORT)
    {
        QDateTime dateTime;
        inStr >> dateTime;
        emit sig_sendTimeToGUI(dateTime);
    }
    else if (port == BIND_PORT_1)
    {
        QString text;
        inStr >> text;
        emit sig_sendTextToGUI(text, address);
    }
}

void UDPworker::SendTextDatagram(QByteArray data)
{
    serviceUdpSocket2->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT_1);
}
/*!
 * @brief Метод осуществляет опередачу датаграммы
 */
void UDPworker::SendDatagram(QByteArray data)
{
    /*
     *  Отправляем данные на localhost и задефайненный порт
     */
    serviceUdpSocket->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT);
}

/*!
 * @brief Метод осуществляет чтение датаграм из сокета
 */
void UDPworker::readPendingDatagrams( void )
{
    /*
     *  Производим чтение принятых датаграмм
     */
    while(serviceUdpSocket->hasPendingDatagrams()){
        QNetworkDatagram datagram = serviceUdpSocket->receiveDatagram();
        ReadDatagram(datagram);
    }



}

void UDPworker::readPendingDatagrams2( void )
{
    while(serviceUdpSocket2->hasPendingDatagrams()){
        QNetworkDatagram datagram = serviceUdpSocket2->receiveDatagram();
        ReadDatagram(datagram);
    }
}
