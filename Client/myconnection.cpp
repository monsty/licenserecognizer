#include "myconnection.h"

MyConnection::MyConnection(QObject *parent) :
    QObject(parent)
{
}

void MyConnection::Connect()
{
    socket = new QTcpSocket(this);

    socket->connectToHost("localhost", 1234);

    if (socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";

        socket->write("logintest\npasstest");
        socket->waitForBytesWritten(1000);

        socket->waitForReadyRead(3000);
        qDebug() << "Reading: " << socket->bytesAvailable();

        qDebug() << socket->readAll();

        socket->close();
    }
    else
    {
        qDebug() << "Not Connected!";
    }
}
