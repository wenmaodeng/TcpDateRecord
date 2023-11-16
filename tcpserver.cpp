#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    
}

TcpServer::~TcpServer()
{
    if(tcpServer)
    {
        tcpServer->close();
        delete  tcpServer;
        tcpServer=nullptr;
    }
    if(currentClient)
    {
        delete currentClient;
        currentClient=nullptr;
    }
}

bool TcpServer::start(int port)
{
	tcpServer = new QTcpServer(this);
	connect(tcpServer, &QTcpServer::newConnection, this, &TcpServer::NewConnectionSlot);
    return tcpServer->listen(QHostAddress::Any, port);
}

bool TcpServer::stop()
{
    if(tcpServer)
    {
        qDebug()<<"stop";
        tcpServer->close();
        tcpServer->deleteLater();
    }

    return true;
}

void TcpServer::sendData(QString data)
{
    for(int i=0; i<tcpClient.length(); i++)
    {
        tcpClient[i]->write(data.toStdString().c_str());
    }
}

void TcpServer::NewConnectionSlot()
{
    currentClient = tcpServer->nextPendingConnection();
    tcpClient.append(currentClient);

    connect(currentClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
}

void TcpServer::disconnectedSlot()
{
    for(int i=0; i<tcpClient.length(); i++)
    {
        if(tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
            tcpClient[i]->destroyed();
            tcpClient.removeAt(i);
        }
    }
}

void TcpServer::ReadData()
{
    for(int i=0; i<tcpClient.length(); i++)
    {
        QByteArray buffer = tcpClient[i]->readAll();
        if(buffer.isEmpty())    continue;
        showServerRecMessage(buffer);
    }
}
