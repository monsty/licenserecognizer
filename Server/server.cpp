#include "server.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{
    pool = new QThreadPool(this);
    pool->setMaxThreadCount(5);
}

void MyServer::StartServer()
{
    if(!this->listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Listening...";
    }
}

void MyServer::incomingConnection(int handle)
{
    MyClient *client = new MyClient(this);
    client->SetSocket(handle);

}
