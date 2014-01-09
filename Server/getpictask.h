#ifndef GETPICTASK_H
#define GETPICTASK_H

#include <QRunnable>
#include <QObject>
#include <QDebug>
#include <QString>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "platedetector.h"

class GetPicTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    GetPicTask(QString path);
    void run();

signals:
    void Result(QString Plate);

private:
    QString _path;
    tesseract::TessBaseAPI *tesseract;

    QString startRecognize(QString fileName);

};

#endif // GETPICTASK_H
