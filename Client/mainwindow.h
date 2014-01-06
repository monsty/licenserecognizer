#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileInfoList>
#include <QStringList>
#include <QTreeWidgetItem>
#include <QList>
#include "myconnection.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(MyConnection *,
                            QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void listFileOnView();

private:
    Ui::MainWindow  *ui;
    MyConnection    *connection;
    QString         fileName;
    QFileInfoList   fileList;
    QString         path;
    QList<QTreeWidgetItem *> updateFileList();
};

#endif // MAINWINDOW_H
