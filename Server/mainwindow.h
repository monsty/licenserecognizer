#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include "database.h"
#include "platedetector.h"
#include "getpictask.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_selectFile_clicked();
    void on_getUsers_clicked();
    void on_deleteUsers_clicked();
    void on_Grayscale_clicked();
    void on_Sobel_clicked();
    void on_Threshold_clicked();
    void on_Draw_Contours_clicked();
    void on_Create_clicked();
    void imageRefresh();
    void on_pushButton_clicked();

private:
    Ui::MainWindow      *ui;
    Database            db;
    platedetector       img;
    QTimer              *autoScan;
    void                load_temp_img();
    void displaySelectedFile(QString fileName);
    int                 file_number;
};

#endif // MAINWINDOW_H
