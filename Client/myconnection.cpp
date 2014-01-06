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
        QImage image;
        qDebug() << "Image to send : " << PathPicToSend;
        image.load(PathPicToSend);
        QString test("");
        QByteArray ba((char *) image.bits(), image.byteCount());
        ba = ba.prepend("\n");
        test = test.number(ba.length() - 1);
        qDebug() << "Size of the picture" << test;
        ba = ba.prepend(test.toStdString().c_str());
        ba = ba.prepend("2\n");
        socket->write(ba);
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
