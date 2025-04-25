#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>


#define BIND_PORT 12345
#define BIND_PORT_1 14999

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);
    void InitSocket( void );
    void ReadDatagram( QNetworkDatagram datagram);
    void SendTextDatagram(QByteArray data );
    void SendDatagram(QByteArray data );


private slots:
    void readPendingDatagrams(void);
    void readPendingDatagrams2(void);

private:
    QHostAddress address;
    int port{0};
    QUdpSocket* serviceUdpSocket;
    QUdpSocket* serviceUdpSocket2;

signals:
    void sig_sendTextToGUI(QString text, QHostAddress address);
    void sig_sendTimeToGUI(QDateTime data);

};

#endif // UDPWORKER_H
