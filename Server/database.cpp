#include "database.h"

Database::Database()
{
    //Database file path setup
    QString tmp_path(QDir::currentPath());
    tmp_path.append(QDir::separator()).append("database.sqlite");
    this->dbpath = QDir::toNativeSeparators(tmp_path);

    // Connection and Initialization
    this->connect();
    this->createTables();

    this->addUser("logintest", "passtest");
    //qDebug() << "user login" << this->userLogin("mOnsty1abc", "azertys");
}

Database::~Database()
{
    db.close();
}

bool Database::connect()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(this->dbpath);
    return this->db.open();
}

bool Database::createTables()
{
    QSqlQuery query(this->db);

    return query.exec("create table if not exists user "
                      "(id integer primary key, "
                      "username varchar(20), "
                      "password varchar(30))");
}

bool Database::userLogin(QString username, QString password)
{
    QSqlQuery query(this->db);

    if (query.exec("select * from user"))
    {
        while (query.next())
        {
            if (query.value(1).toString().compare(username.toLower()) == 0 &&
                query.value(2).toString().compare(password) == 0)
            {
                qDebug() << "login OK";
                return true;
            }
        }
    }

    qDebug() << "login NOK";
    return false;
}

bool Database::addUser(QString username, QString password)
{
    QSqlQuery query(this->db);

    if (!query.exec(QString("select * from user where username='%1'").arg(username.toLower())))
        return false;

    while (query.next())
    {
        if (query.value(1).toString().compare(username.toLower()) == 0)
        {
            qDebug() << "user" << username << "already exist, add failed";
            return false;
        }
    }

    int id;
    if (username.toLower() == "logintest"){
        id  = 1;
    }
    else
    {
        id = NULL;
    }

    if (query.exec(QString("insert into user values('%0','%1','%2')").arg(id).arg(username.toLower()).arg(password)))
    {
        qDebug() << "user" << username << "added";
        return true;
    }
    else
    {
        qDebug() << "error while adding user" << username;
        return false;
    }
}

bool Database::deleteUser(QString username) {
    QSqlQuery query(this->db);

    if (query.exec(QString("select * from user where username='%1'").arg(username.toLower())))
    {
        query.exec(QString("delete from user where username='%1'").arg(username.toLower()));
        qDebug() << "user" << username << "deleted.";
    }
    else
    {
        return false;
    }

    return true;
}

QSqlQueryModel* Database::getUsers() {
    QSqlQuery query(this->db);

    QSqlQueryModel *model = new QSqlQueryModel();
    query.exec(QString("select * from user"));

    model->setQuery(query);

    return model;
}
