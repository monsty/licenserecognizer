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
    QImage image(PathPicToSend);

    //QByteArray ba;
    //QBuffer buffer(&ba);
    //image.save(&buffer, PathPicToSend.mid(PathPicToSend.length() - 3).toUpper());
    //QByteArray ba = qCompress(image.bits());
    QByteArray ba((char *) image.bits(), image.byteCount());
    socket->write(ba.prepend("2"));
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
