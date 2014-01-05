#ifndef ANALYZEPICTASK_H
#define ANALYZEPICTASK_H

#include <QRunnable>
#include <QObject>
#include <QDebug>

class AnalyzePicTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    AnalyzePicTask();    

protected:
    void run();

signals:
    void Result(int Number);

};

#endif // ANALYZEPICTASK_H
