#ifndef GETPICTASK_H
#define GETPICTASK_H

#include <QRunnable>
#include <QObject>
#include <QDebug>

class GetPicTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    GetPicTask();

protected:
    void run();

signals:
    void Result(int Number);

};

#endif // GETPICTASK_H
