#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>

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
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open File"),"/path/to/file/");
    //ui->listWidget->addItems(fileNames);
}
