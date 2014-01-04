#include "mytask.h"
#include "database.h"

MyTask::MyTask(QString login, QString pass)
{
    _login = login;
    _pass = pass;
}

void MyTask::run()
{
    qDebug() << "Login started";

    Database db;

    if (db.userLogin(_login, _pass) == true)
    {
        qDebug() << "Login success";
        emit Result(1);
    }
    else
    {
        qDebug() << "Login failed";
        emit Result(0);
    }
}
