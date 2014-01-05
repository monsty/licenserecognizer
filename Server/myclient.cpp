#include "myclient.h"

MyClient::MyClient(QObject *parent) :
    QObject(parent)
{
    isLoggedIn = false;
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

}

void MyClient::disconnected()
{
    qDebug() << "client disconnected";
}

void MyClient::readyRead()
{
    QByteArray LoginPass = socket->readAll();
    QList<QByteArray> res = LoginPass.split('\n');
    qDebug() << " Login: " << res[0];
    qDebug() << " Pass: " << res[1];

    MyTask *mytask = new MyTask(res[0], res[1]);
    mytask->setAutoDelete(true);
    connect(mytask, SIGNAL(Result(int)), this, SLOT(TaskResult(int)), Qt::QueuedConnection);
    QThreadPool::globalInstance()->start(mytask);
}

void MyClient::TaskResult(int Number)
{
    QByteArray Buffer;
    Buffer.append(QString::number(Number));
    if (Number == 1)
        isLoggedIn = true;
    socket->write(Buffer);
}
