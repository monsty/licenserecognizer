#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>

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
    QPixmap pm(fileName);

    //qDebug() << parts.at(parts.size() - 1);
    ui->label_3->setText(parts.at(parts.size() - 1));
    ui->label->setPixmap(pm);
}
