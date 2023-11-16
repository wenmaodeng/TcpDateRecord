#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDateTime>
#include <QTimer>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient(QString _serverDes, QObject *parent = nullptr);
    ~TcpClient();
    Q_PROPERTY(QString ip READ getIp WRITE setIp);
    Q_PROPERTY(int port READ getPort WRITE setPort);

    Q_INVOKABLE bool  connectToServer(QString ip, int port);
    Q_INVOKABLE void  stop();
    Q_INVOKABLE void sendData(QString data);

    QString getIp() const;
    void setIp(const QString &value);

    int getPort() const;
    void setPort(int value);

private:
    QTcpSocket *tcpClient=nullptr;
    QString Ip;
    int Port;
    QTimer *timer=nullptr;

    QDateTime lastRcvDataTime;
    QString serverDes;

private slots:
    //¿Í»§¶Ë²Ûº¯Êý
    void ReadData();
    void heartBeat();
    void ReadError(QAbstractSocket::SocketError);
signals:
    void triggerClientRecData(QString data);
    void triggerError(QString data);
};

#endif // TCPCLIENT_H
