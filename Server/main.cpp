#include "mainwindow.h"
#include "server.h"
#include "database.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //Database db;
    MyServer s;

    s.StartServer();

    return a.exec();
}
