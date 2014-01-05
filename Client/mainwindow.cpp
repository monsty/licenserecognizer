#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageviewer.h"
#include <qfiledialog.h>
#include <qdebug.h>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.bmp *.jpg)"));
    QStringList parts = fileName.split("/");

    qDebug() << parts.at(parts.size() - 1);
    ui->label_2->setText(parts.at(parts.size() - 1));
}

void resizePmap(QPixmap &pmap)
{
    QSize size;
    size.setHeight(50); // 67
    size.setWidth(80); // 100
    pmap = QPixmap(size);
}

void MainWindow::on_pushButton_2_clicked()
{
    QPixmap pm("/Users/lisan/Pictures/bored.jpg");

    //resizePmap(pm);

    //pm.scaled(50, 80);
    ui->myLabel->setPixmap(pm);
    //qDebug() << "Testing show image";
    ui->myLabel->show();
}
