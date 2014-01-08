#ifndef GETPICTASK_H
#define GETPICTASK_H

#include <QRunnable>
#include <QObject>
#include <QDebug>
#include <QString>

class GetPicTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    GetPicTask();

protected:
    void run();

signals:
    void Result(String Plate);

private:
    QString_path;

};

#endif // GETPICTASK_H
