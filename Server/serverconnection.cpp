#include "serverconnection.h"
#include "ui_serverconnection.h"

ServerConnection::ServerConnection(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerConnection)
{
    this->ui->setupUi(this);
}

ServerConnection::~ServerConnection()
{
    delete ui;
}


void ServerConnection::on_loginButton_clicked()
{
    QString password = ui->serverPass->text();
    if(!db.userLogin("admin", password))
    {
        qDebug() << "Incorrect password.";
    }
    else
    {
        this->mainWindow = new MainWindow();
        this->mainWindow->show();
        this->close();
    }
}
