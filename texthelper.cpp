#include "texthelper.h"

TextHelper::TextHelper(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(heartSendData()));
}

bool TextHelper::writeData(QString filename,QString data)
{
    filename=filename.replace("file:///","");
    qDebug()<<filename;
    qDebug()<<data;
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return  false;
    }
    else
    {
        file.write(data.toUtf8());
        file.close();
    }
    return true;
}

bool TextHelper::readData(QString filename)
{
    filename=filename.replace("file:///","");
    data.clear();
    _index=0;
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QTextStream stream(&file);
    while(!stream.atEnd())
    {
        QString line = stream.readLine();
        data.push_back(line);
    }
    file.close();
    return true;
}

void TextHelper::startSendData()
{
    if(!timer->isActive())
        timer->start(200);
}

void TextHelper::stopSendData()
{
    timer->stop();
    data.clear();
    _index=0;
}


void TextHelper::heartSendData()
{
    if(_index<data.size())
    {
        sendData(data.at(_index));
        _index++;
        QString temp="%1/%2";
        countInfo(temp.arg(_index).arg(data.size()));
    }
    else
    {
        stopSendData();
    }
}
