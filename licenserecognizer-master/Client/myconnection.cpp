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
