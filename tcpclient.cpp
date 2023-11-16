#include "tcpclient.h"

TcpClient::TcpClient(QString _serverDes, QObject *parent)
{
    Q_UNUSED(parent);
    tcpClient = new QTcpSocket(this);
    tcpClient->abort();
    serverDes = _serverDes;
    timer = new QTimer(this);
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(ReadError(QAbstractSocket::SocketError)));
    connect(timer, SIGNAL(timeout()), this, SLOT(heartBeat()));
}

TcpClient::~TcpClient()
{
    qDebug()<<"close tcpclient";
    if(timer)
    {
        timer->stop();
        delete timer;
        timer=nullptr;
    }
    if(tcpClient)
    {
        tcpClient->disconnectFromHost();
        delete tcpClient;
        tcpClient=nullptr;
    }
}

bool TcpClient::connectToServer(QString _ip, int _port)
{
    setIp(_ip);
    setPort(_port);
    tcpClient->connectToHost(_ip, _port);
    lastRcvDataTime = QDateTime::currentDateTime();
    timer->start(5000);
    if (tcpClient->waitForConnected(1000))  // 连接成功则进入if{}
    {
        return  true;
    }
    else
    {
        return  false;
    }
}

void TcpClient::stop()
{
    tcpClient->close();
    timer->stop();
}

void TcpClient::sendData(QString data)
{
    tcpClient->write(data.toStdString().c_str());
}

QString TcpClient::getIp() const
{
    return Ip;
}

void TcpClient::setIp(const QString &value)
{
    Ip = value;
}

int TcpClient::getPort() const
{
    return Port;
}

void TcpClient::setPort(int value)
{
    Port = value;
}

void TcpClient::ReadData()
{
    QByteArray buffer = tcpClient->readAll();
    if(!buffer.isEmpty())
    {
        triggerClientRecData(buffer);
        lastRcvDataTime= QDateTime::currentDateTime();
    }
}

void TcpClient::ReadError(QAbstractSocket::SocketError)
{
    triggerError(tcpClient->errorString());
}

void TcpClient::heartBeat()
{
    QDateTime temp= QDateTime::currentDateTime();

    if (lastRcvDataTime.secsTo(temp) > 5)
    {
        lastRcvDataTime=QDateTime::currentDateTime();
        tcpClient->abort();
        tcpClient->connectToHost(getIp(), getPort());
    }
}
