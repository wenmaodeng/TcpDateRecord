#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "tcpclient.h"
#include "tcpserver.h"
#include "texthelper.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    TcpClient *tcpClient=new TcpClient("接收数据");
    TcpServer *tcpServer=new TcpServer();
    TextHelper *textHelper=new TextHelper();

    QObject::connect(textHelper,&TextHelper::sendData,tcpServer,&TcpServer::sendData);

    engine.rootContext()->setContextProperty("tcpClient",tcpClient);
    engine.rootContext()->setContextProperty("tcpServer",tcpServer);
    engine.rootContext()->setContextProperty("textHelper",textHelper);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    app.exec();

    if(tcpClient)
    {
        delete tcpClient;
    }
    if(tcpServer)
    {
        delete tcpServer;
    }

    return 0;
}
