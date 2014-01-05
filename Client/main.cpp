#include "connectionwindow.h"
#include <QApplication>
#include <stdio.h>
#include <sys/types.h>
//#include <dirent.h>
#include <qdebug.h>
#include "myconnection.h"

void scanDir()
{
    /*
    DIR *dir = opendir(".");

    if (dir)
    {
        struct dirent *ent;
        while((ent = readdir(dir)) != NULL)
        {
            qDebug() << ent->d_name;
        }
    }
    else
    {
        fprintf(stderr, "Error opening directory\n");
    }
    */
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnectionWindow w;
    w.show();

    //scanDir();
    return a.exec();
}
