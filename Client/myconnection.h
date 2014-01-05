#ifndef MYCONNECTION_H
#define MYCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QImage>
#include <QBuffer>

class MyConnection : public QObject
{
    Q_OBJECT
public:
    explicit MyConnection(QObject *parent = 0);
    void Connect();
    void Disconnect();
    void Send(QString toSend);
    void SendPic(QString PathPicToSend);
    QString Read();

signals:

public slots:

private:
    QTcpSocket *socket;

public:
    bool isConnected;

};

#endif // MYCONNECTION_H
