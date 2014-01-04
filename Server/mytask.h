#ifndef MYTASK_H
#define MYTASK_H

#include <QRunnable>
#include <QObject>
#include <QDebug>

class MyTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    MyTask();

protected:
    void run();

signals:
    void Result(int Number);

};

#endif // MYTASK_H
