#include "logintask.h"
#include "database.h"

LoginTask::LoginTask(QString login, QString pass)
{
    _login = login;
    _pass = pass;
}

void LoginTask::run()
{
    qDebug() << "Login started";

    Database db;

    db.addUser("qqq", "aaa");

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
