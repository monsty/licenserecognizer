#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QDir>

class Database
{
public:
    Database();

private:
    QSqlDatabase db;
    QString dbpath;
    bool connect();
    bool createTables();

public:
    bool userLogin(QString username, QString password);
    bool addUser(QString username, QString password);
};

#endif // DATABASE_H
