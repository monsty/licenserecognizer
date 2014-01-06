#include "myclient.h"

MyClient::MyClient(QObject *parent) :
    QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(5);
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
    QByteArray Datas = socket->readAll();
    QList<QByteArray> DatasList = Datas.split('\n');
    if (DatasList[0] == "1")
    {
        qDebug() << " Launch login task ";
        QByteArray LoginPass = Datas.mid(2);
        QList<QByteArray> res = LoginPass.split('\n');
        qDebug() << " Login: " << res[0];
        qDebug() << " Pass: " << res[1];

        LoginTask *logintask = new LoginTask(res[0], res[1]);
        logintask->setAutoDelete(true);
        connect(logintask, SIGNAL(Result(int)), this, SLOT(TaskResult(int)), Qt::QueuedConnection);
        QThreadPool::globalInstance()->start(logintask);
    }
    else if (DatasList[0] == "2")
    {
        qDebug() << " Launch getPic task ";
        QByteArray Picture = Datas.mid(DatasList[0].length() + DatasList[1].length() + 2);
        int size = DatasList[1].toInt();
        qDebug() << "Size I expect " << size;
        int received = Picture.length();
        while(received < size)
        {
            QByteArray newRec = socket->readAll();
            socket->waitForReadyRead(300);
            received += newRec.length();
            Picture += newRec;
        }
        QImage image;
        qDebug() << "Picture Size = " << Picture.length();
        image.loadFromData(Picture);
        image.save("test.jpg");
    }
    else
    {
        qDebug() << " Launch other task ";
    }
}

void MyClient::TaskResult(int Number)
{
    QByteArray Buffer;
    Buffer.append(QString::number(Number));
    if (Number == 1)
        isLoggedIn = true;
    socket->write(Buffer);
}
