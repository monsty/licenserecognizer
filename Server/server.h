#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>

#include "mythread.h"

class MyServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit MyServer(QObject *parent = 0);
    void StartServer();

signals:

public slots:

private:

protected:
    void incomingConnection(int socketDescriptor);

};

#endif // SERVER_H
