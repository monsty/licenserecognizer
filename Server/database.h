#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QDir>
#include <QSqlQueryModel>

class Database
{
public:
    Database();
    ~Database();
    QSqlDatabase db;


private:
    QString dbpath;
    bool createTables();

public:

    bool userLogin(QString username, QString password);
    bool addUser(QString username, QString password);
    bool deleteUser(QString username);
    QSqlQueryModel* getUsers();
    bool connect();

};

#endif // DATABASE_H
