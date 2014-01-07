#include "myconnection.h"

MyConnection::MyConnection(QObject *parent) :
    QObject(parent)
{
    this->socket = new QTcpSocket(this);
    this->isConnected = false;
}

void MyConnection::Connect()
{
    this->socket->connectToHost("localhost", 1234);

    if (this->socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";
        this->isConnected = true;
    }
    else
    {
        qDebug() << "Connection failed!";
        this->isConnected = false;
    }
}

void MyConnection::Send(QString toSend)
{
    if (this->isConnected)
    {
        this->socket->write(toSend.toStdString().c_str());
        this->socket->waitForBytesWritten(1000);
    }
}

void MyConnection::SendPic(QString PathPicToSend)
{
    if (this->isConnected)
    {
        qDebug() << "Image to send : " << PathPicToSend;

        QString file_size("");
        QByteArray data;

        QFile file(PathPicToSend);
        file.open(QIODevice::ReadOnly);
        data = file.readAll();
        file.close();

        file_size = file_size.number(data.length());
        qDebug() << "Size of the picture" << file_size;

        data = data.prepend("\n");
        data = data.prepend(file_size.toStdString().c_str());
        data = data.prepend("2\n");

        socket->write(data);
        socket->waitForBytesWritten(1000);
    }
}

QString MyConnection::Read()
{
    if (this->isConnected)
    {
        this->socket->waitForReadyRead(3000);
        //qDebug() << "Reading: " << socket->bytesAvailable();
        return this->socket->readAll();
    }
}

void MyConnection::Disconnect()
{
    if (this->isConnected)
    {
        this->socket->close();
        this->isConnected = false;
    }
}
