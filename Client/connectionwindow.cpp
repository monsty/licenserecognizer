#include "connectionwindow.h"
#include "ui_connectionwindow.h"

ConnectionWindow::ConnectionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectionWindow)
{
    ui->setupUi(this);

    this->connection = new MyConnection();
    this->connection->Connect();

    if (this->connection->isConnected == false)
        ui->statusbar->showMessage("The server is not responding ...");

    this->mainWindow = new MainWindow(this->connection);
}

ConnectionWindow::~ConnectionWindow()
{
    delete ui;
}

void ConnectionWindow::on_loginButton_clicked()
{
    QString loginPassword;

    if (this->connection->isConnected)
    {
        loginPassword = '1'+ ui->loginEdit->text() + '\n' + ui->passwordEdit->text();

        this->connection->Send(loginPassword);

        if (this->connection->Read() == "1")
        {
            this->mainWindow->show();
            this->close();
        }
        else
        {
            ui->label->setText("wrong login or password");
        }
    }
    else
    {
        ui->label->setText("the server is not responding ...");

    }
}
