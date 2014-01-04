#include "mytask.h"

MyTask::MyTask()
{
}

void MyTask::run()
{
    qDebug() << "Task Started";

    int iNumber = 0;
    for (int i = 0; i < 1000; i++)
    {
        iNumber += 1;
    }

    qDebug() << "Task Finished";
    emit Result(iNumber);
}
