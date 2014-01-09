#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QDebug>
#include <QSqlQuery>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->show();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //load_temp_img();

    this->autoScan = new QTimer();
    this->autoScan->connect(this->autoScan, SIGNAL(timeout()), this, SLOT(imageRefresh()));
    this->autoScan->start(100);

    this->file_number = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.bmp *.jpg)"));
    this->img.set_original(fileName.toStdString().c_str());
    ui->label->setPixmap(this->img.get_original());
    displaySelectedFile(fileName);
    this->autoScan->stop();
}

void MainWindow::on_getUsers_clicked()
{
    QSqlQueryModel *model;
    model = db.getUsers();

    ui->tableView->setModel(model);
}

void MainWindow::on_deleteUsers_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();

    int index = ui->tableView->selectionModel()->currentIndex().row();
    QString username = ui->tableView->model()->data(ui->tableView->model()->index(index,1)).toString();
    qDebug() << "Selected user: " << username;
    db.deleteUser(username);
}

void MainWindow::on_Grayscale_clicked()
{
    this->img.set_gray();
    ui->label->setPixmap(this->img.get_gray());
}

void MainWindow::on_Sobel_clicked()
{
    this->img.set_sobel();
    ui->label->setPixmap(this->img.get_sobel());
}

void MainWindow::on_Threshold_clicked()
{
    this->img.set_threshold();
    ui->label->setPixmap(this->img.get_threshold());
}

void MainWindow::on_Draw_Contours_clicked()
{
    this->img.set_contours();
    ui->label->setPixmap(this->img.get_contours());
}

void MainWindow::on_Create_clicked()
{
    this->img.crop_img();
}

void MainWindow::imageRefresh() {
    displaySelectedFile("temp_file.jpg");
}

void MainWindow::displaySelectedFile(QString fileName) {
    this->img.set_original(fileName.toStdString().c_str());
    ui->label->setPixmap(this->img.get_original());

    QStringList parts = fileName.split("/");
    QString name = "File name: ";
    name.append(QString(parts.at(parts.size() - 1)));
    ui->label_3->setText(name);
}


void MainWindow::on_pushButton_clicked()
{
    QString filename = "/Users/antoinela/BJTU_Projects/Project Software Training 1/PublicResource/Licence/workplace/Level_1/初出茅庐0";
    if (this->file_number < 10)
    {
        filename.append("0");
        filename.append(QString::number(this->file_number));
    }
    else
    {
        filename.append(QString::number(this->file_number));
    }
    filename.append(".jpg");

    this->file_number++;
    if (this->file_number > 26)
        this->file_number = 1;

    GetPicTask task(filename);
    task.run();
}
