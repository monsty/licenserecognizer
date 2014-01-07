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
#include <QTimer>
#include "myconnection.h"

namespace Ui {
    class MainWindow;
}

struct MyFile
{
    QString name;
    QString path;
    QString plate;
    bool    sent;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(MyConnection *, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void listFileOnView();
    void on_selectDirectory_clicked();
    void on_recognize_clicked();
    void on_checkBox_stateChanged(int arg1);

public slots:
    void myTreeSelectionChanged(const QItemSelection & selected);
    void directoryRefresh();


private:
    Ui::MainWindow  *ui;
    MyConnection    *connection;
    QString         selectedFile;
    QString         directoryPath;
    QList<MyFile>   fileList;
    QTimer          *autoScan;

    void updateFileList();
};


#endif // MAINWINDOW_H
