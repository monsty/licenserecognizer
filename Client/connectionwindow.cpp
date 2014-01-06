#include "connectionwindow.h"
#include "ui_connectionwindow.h"

ConnectionWindow::ConnectionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectionWindow)
{
    this->mainWindow = new MainWindow(this->connection);
    this->mainWindow->show();
    this->close();

   /* ui->setupUi(this);
    this->connection = new MyConnection();
    this->connection->Connect();
    this->mainWindow = new MainWindow(this->connection);*/
}

ConnectionWindow::~ConnectionWindow()
{
    delete ui;
}

void ConnectionWindow::on_pushButton_clicked()
{
    QString loginPassword;

    loginPassword = '1'+ ui->lineEdit->text()
            + '\n'+ ui->lineEdit_2->text();
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
