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
    GetPicTask(QString path);

protected:
    void run();

signals:
    void Result(QString Plate);

private:
    QString _path;

};

#endif // GETPICTASK_H
