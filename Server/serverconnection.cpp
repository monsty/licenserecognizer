#include "serverconnection.h"
#include "ui_serverconnection.h"
#include <qcryptographichash.h>


ServerConnection::ServerConnection(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerConnection)
{
    this->ui->setupUi(this);
    this->ui->serverPass->setEchoMode(QLineEdit::Password);
}

ServerConnection::~ServerConnection()
{
    delete ui;
}


void ServerConnection::on_loginButton_clicked()
{
    QString password = ui->serverPass->text();
    QString hashserverpass = QString(QCryptographicHash::hash(("12345"),QCryptographicHash::Md5).toHex());
    QString hashloginpass = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex());

    if(hashserverpass != hashloginpass)
    {
        ui->loginStatus->setText("Password incorrect.");
    }
    else
    {
        this->mainWindow = new MainWindow();
        this->mainWindow->show();
        this->close();
    }
}
