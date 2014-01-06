#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <qdebug.h>
#include <QFile>

MainWindow::MainWindow(MyConnection *connect,
                        QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->connection = new MyConnection();
    this->connection = connect;
    this->fileName = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.bmp *.jpg)"));
    QStringList parts = fileName.split("/");
    QPixmap pm(fileName);

    //qDebug() << parts.at(parts.size() - 1);
    ui->label_3->setText(parts.at(parts.size() - 1));
    ui->label_2->setPixmap(pm);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString     fileNameToSend;

    fileNameToSend = '2' + this->fileName;
    this->connection->SendPic(fileNameToSend);
}
