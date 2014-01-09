#ifndef LOGINTASK_H
#define LOGINTASK_H

#include <QRunnable>
#include <QObject>
#include <QDebug>

class LoginTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    LoginTask(QString login, QString pass);


protected:
    void run();

signals:
    void Result(int Number);

private:
    QString _login;
    QString _pass;
};

#endif // LOGINTASK_H
