#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &TcpServer::NewConnectionSlot);
}

TcpServer::~TcpServer()
{
    qDebug()<<"close tcpserver";
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

bool TcpServer::start(QString ip,int port)
{
    bool ok = tcpServer->listen(QHostAddress(ip), port);
    if(ok)
    {
        qDebug()<<"start success";
    }
    else
    {
        qDebug()<<"start fail";
    }
    return  ok;
}

bool TcpServer::stop()
{
    if(tcpServer)
        tcpServer->close();
    return true;
}

void TcpServer::sendData(QString data)
{
    qDebug()<<"server send:"<<data;
    for(int i=0; i<tcpClient.length(); i++)
    {
        tcpClient[i]->write(data.toStdString().c_str());
    }

}

void TcpServer::NewConnectionSlot()
{

    qDebug()<<"NewConnectionSlot";
    currentClient = tcpServer->nextPendingConnection();
    tcpClient.append(currentClient);

    connect(currentClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));

}

void TcpServer::disconnectedSlot()
{
    //����disconnected�źŲ�δ�ṩSocketDescriptor��������Ҫ����Ѱ��
    for(int i=0; i<tcpClient.length(); i++)
    {
        if(tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
            qDebug()<<"client disconnect:"<<"ip:"<<tcpClient[i]->peerAddress().toString()<<"port:"<<tcpClient[i]->peerPort();

            tcpClient[i]->destroyed();
            tcpClient.removeAt(i);
        }
    }
}

void TcpServer::ReadData()
{
    // ����readyRead�źŲ�δ�ṩSocketDecriptor��������Ҫ�������пͻ���
    for(int i=0; i<tcpClient.length(); i++)
    {
        QByteArray buffer = tcpClient[i]->readAll();
        if(buffer.isEmpty())    continue;

        qDebug()<<"server rec data:"<<buffer;
        showServerRecMessage(buffer);
    }
}
