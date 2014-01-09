#include "connectionwindow.h"
#include "ui_connectionwindow.h"

ConnectionWindow::ConnectionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectionWindow)
{
    this->ui->setupUi(this);
    this->ui->passwordEdit->setEchoMode(QLineEdit::Password);
    this->connection = new MyConnection();
    this->connection->Connect();
    if (this->connection->isConnected == false)
        ui->statusbar->showMessage("The server is not responding ...");
}

ConnectionWindow::~ConnectionWindow()
{
    delete ui;
}

void ConnectionWindow::on_loginButton_clicked()
{
    if (this->connection->isConnected)
    {
        this->connection->Send('1' + ui->loginEdit->text() + '\n' + ui->passwordEdit->text());
        if (this->connection->Read() == "1")
        {
            this->mainWindow = new MainWindow(this->connection);
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
