#include "serverconnection.h"
#include "server.h"
#include "database.h"
#include <QApplication>
//#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerConnection w;
    w.show();

    //Database db;
    MyServer *s;

    s = new MyServer;
    s->StartServer();

    return a.exec();
}
