#include "getpictask.h"

GetPicTask::GetPicTask(QString picPath)
{
    _path = picPath;
}

void GetPicTask::run()
{
    emit Result("TEST04");
}
