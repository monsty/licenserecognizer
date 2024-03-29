#ifndef MYCLIENT_H
#define MYCLIENT_H

#include "logintask.h"
#include "getpictask.h"

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include <QImage>
#include <QDir>
#include <QBuffer>

class MyClient : public QObject
{
    Q_OBJECT
public:
    explicit MyClient(QObject *parent = 0);
    void SetSocket(int Descriptor);

signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void TaskResult(int Number);
    void TaskResult(QString Plate);

private:
    QTcpSocket *socket;
    bool isLoggedIn;
};

#endif // MYCLIENT_H
