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

    qDebug() << "received:" << Datas;

    if (DatasList[0][0] == '1')
    {
        qDebug() << " Launch login task ";
        QByteArray LoginPass = Datas.mid(1);
        QList<QByteArray> res = LoginPass.split('\n');
        qDebug() << " Login: " << res[0];
        qDebug() << " Pass: " << res[1];

        LoginTask *logintask = new LoginTask(res[0], res[1]);
        logintask->setAutoDelete(true);
        connect(logintask, SIGNAL(Result(int)), this, SLOT(TaskResult(int)), Qt::QueuedConnection);
        QThreadPool::globalInstance()->start(logintask);
    }
    else if (DatasList[0][0] == '2')
    {
        qDebug() << " Launch getPic task ";

        QByteArray newRec;

        int size = DatasList[1].toInt();
        int received = Datas.length();
        while(received < size)
        {
            newRec = socket->readAll();
            socket->waitForReadyRead(300);
            received += newRec.length();
            Datas += newRec;
        }
        Datas.remove(0, 2 + DatasList[1].length() + 1);

        QString tmp_path(QDir::currentPath());
        tmp_path.append(QDir::separator()).append("temp_file.jpg");
        QFile file(QDir::toNativeSeparators(tmp_path));
        file.open(QIODevice::WriteOnly);
        file.write(Datas);
        file.close();

        GetPicTask *pictask = new GetPicTask(tmp_path);
        pictask->setAutoDelete(true);
        connect(pictask, SIGNAL(Result(QString)), this, SLOT(TaskResult(QString)), Qt::QueuedConnection);
        QThreadPool::globalInstance()->start(pictask);
        qDebug() << "Trying to save" << QDir::toNativeSeparators(tmp_path);
        qDebug() << "File size expected" << size;
        qDebug() << "File size received " << Datas.length();
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

void MyClient::TaskResult(QString Plate)
{
    QByteArray Buffer;
    Buffer.append(Plate);
    socket->write(Buffer);
}
