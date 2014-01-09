#include "getpictask.h"

GetPicTask::GetPicTask(QString picPath)
{
    _path = picPath;
}

void GetPicTask::run()
{
    platedetector   detector;
    std::vector<QString>    cropped_list;

    cropped_list = detector.run(this->_path.toStdString().c_str());

    emit Result("TEST04");
}
