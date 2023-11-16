#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QNetworkProxyFactory>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    ~TcpServer();
    Q_INVOKABLE bool start(int port);
    Q_INVOKABLE bool stop();
    Q_INVOKABLE void sendData(QString data);

signals:
    void showServerRecMessage(QString data);
private slots:
    void NewConnectionSlot();
    void disconnectedSlot();
    void ReadData();
private:
    QTcpServer *tcpServer=nullptr;
    QList<QTcpSocket*> tcpClient;
    QTcpSocket *currentClient=nullptr;
};

#endif // TCPSERVER_H
