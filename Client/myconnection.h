#ifndef MYCONNECTION_H
#define MYCONNECTION_H

#include <QObject>
#include <QTcpSocket>

class MyConnection : public QObject
{
    Q_OBJECT
public:
    explicit MyConnection(QObject *parent = 0);
    void Connect();
    void Disconnect();
    void Send(QString toSend);
    QString Read();

signals:

public slots:

private:
    QTcpSocket *socket;
    bool isConnected;

};

#endif // MYCONNECTION_H
