#include "server.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{
}

void MyServer::StartServer()
{
    //connect(this, SIGNAL(newConnection()), SLOT(incomingConnection()));
    if(!this->listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Listening...";
    }

}

void MyServer::incomingConnection(qintptr handle)
{
    MyClient *client = new MyClient(this);
    client->SetSocket(handle);
}
