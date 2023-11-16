#ifndef TEXTHELPER_H
#define TEXTHELPER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QTimer>

class TextHelper : public QObject
{
    Q_OBJECT
public:
    explicit TextHelper(QObject *parent = nullptr);

    Q_INVOKABLE bool  writeData(QString filename,QString data);
    Q_INVOKABLE bool readData(QString filename);
    Q_INVOKABLE void startSendData();
    Q_INVOKABLE void stopSendData();

private:
    std::vector<QString> data;
    QTimer *timer=nullptr;
    unsigned int _index=0;
signals:
    void sendData(QString data);
    void countInfo(QString info);
private slots:
    void heartSendData();

};

#endif // TEXTHELPER_H
