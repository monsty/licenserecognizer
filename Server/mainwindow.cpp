#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QDebug>
#include <QSqlQuery>
#include <QModelIndex>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->show();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

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
    QPixmap pm_2;

    //qDebug() << parts.at(parts.size() - 1);

    cv::Mat mat;
    cv::Mat output_mat;
    cv::Mat sobel_mat;
    cv::Mat threshold_mat;

    mat = cv::imread(fileName.toStdString().c_str(), CV_LOAD_IMAGE_COLOR);
    cv::cvtColor(mat, output_mat, CV_BGR2GRAY);
    cv::blur(output_mat, output_mat, cv::Size(5,5));
    cv::Sobel(output_mat, sobel_mat, CV_8U, 1, 0, 3, 1, 0);
    cv::threshold(sobel_mat, threshold_mat, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);

    cv::namedWindow("recognition", cv::WINDOW_AUTOSIZE);
    imshow("recognition", threshold_mat);
    pm_2 = QPixmap::fromImage(QImage((unsigned char*) output_mat.data, output_mat.cols, output_mat.rows, QImage::Format_RGB888));

    ui->label_3->setText(parts.at(parts.size() - 1));
    ui->label->setPixmap(pm_2);

    qDebug() << fileName;
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_pushButton_3_clicked()
{

    QSqlQueryModel *model;
    model = db.getUsers();

    ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_4_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();

    int index = ui->tableView->selectionModel()->currentIndex().row();
    QString username = ui->tableView->model()->data(ui->tableView->model()->index(index,1)).toString();

    qDebug() << "Selected user: " << username;

    db.deleteUser(username);

}
