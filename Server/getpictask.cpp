#include "getpictask.h"

GetPicTask::GetPicTask(QString picPath)
{
    _path = picPath;
}

void GetPicTask::run()
{
    qDebug() << "analizing plate....";
    emit Result("TEST04");
}
