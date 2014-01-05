#ifndef MYTASK_H
#define MYTASK_H

#include <QRunnable>
#include <QObject>
#include <QDebug>

class MyTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    MyTask(QString login, QString pass);

protected:
    void run();

signals:
    void Result(int Number);

private:
    QString _login;
    QString _pass;
};

#endif // MYTASK_H
