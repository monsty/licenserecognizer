#include "myclient.h"

MyClient::MyClient(QObject *parent) :
    QObject(parent)
{

}

void MyClient::SetSocket(int Descriptor)
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));

    socket->setSocketDescriptor(Descriptor);

    qDebug() << "client connected";
}

void MyClient::connected()
{
    QByteArray Buffer;
    Buffer.append("Coucou");
    socket->write(Buffer);

}

void MyClient::disconnected()
{
    qDebug() << "client disconnected";
}

void MyClient::readyRead()
{
    QByteArray Data = socket->readAll();

    qDebug() << " Data in: " << Data;

    MyTask *mytask = new MyTask();
    mytask->setAutoDelete(true);
    connect(mytask, SIGNAL(Result(int)), this, SLOT(TaskResult(int)), Qt::QueuedConnection);
    QThreadPool::globalInstance()->start(mytask);
}

void MyClient::TaskResult(int Number)
{
    QByteArray Buffer;
    Buffer.append("\r\nTask Result = ");
    Buffer.append(QString::number(Number));

    socket->write(Buffer);
}
