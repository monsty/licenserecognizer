#include "connectionwindow.h"
#include <QApplication>
#include <stdio.h>
#include <sys/types.h>
//#include <dirent.h>
#include <qdebug.h>
#include "myconnection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnectionWindow w;
    w.show();
    return a.exec();
}
