#include "myconnection.h"

MyConnection::MyConnection(QObject *parent) :
    QObject(parent)
{
    socket = new QTcpSocket(this);
    isConnected = false;
}

void MyConnection::Connect()
{
    socket->connectToHost("localhost", 1234);

    if (socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";
        isConnected = true;
    }
    else
    {
        qDebug() << "Not Connected!";
    }
}

void MyConnection::Send(QString toSend)
{
    socket->write(toSend.toStdString().c_str());
    socket->waitForBytesWritten(1000);
}

void MyConnection::SendPic(QString PathPicToSend)
{
    QImage image;
    qDebug() << "Image to send : " << PathPicToSend;
    image.load(PathPicToSend);
    QString test("");
    QByteArray ba((char *) image.bits(), image.byteCount());
    ba = ba.prepend("\n");
    test = test.number(ba.length() - 1);
    qDebug() << "Size of the picture i send" << test;
    ba = ba.prepend(test.toStdString().c_str());
    ba = ba.prepend("2\n");
    socket->write(ba);
    socket->waitForBytesWritten(1000);
}

QString MyConnection::Read()
{
    socket->waitForReadyRead(3000);
    //qDebug() << "Reading: " << socket->bytesAvailable();
    return socket->readAll();
}

void MyConnection::Disconnect()
{
    socket->close();
}
