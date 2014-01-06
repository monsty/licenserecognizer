#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MyConnection *connect,
                        QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->connection = new MyConnection();
    this->connection = connect;
    this->fileName = "";
    this->fileList = get_filenames("/home");

    QStringList list;
    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < this->fileList.size(); ++i)
    {
        list.push_back(this->fileList.at(i).fileName());
        items.append(new QTreeWidgetItem((QTreeWidget*)0,
                                            QStringList(QString(list[i]).arg(i))));
    }
    ui->treeWidget->insertTopLevelItems(0, items);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QFileInfoList MainWindow::get_filenames(QString path)
{
    QDir dir;

    dir.cd(path);
    QFileInfoList list = dir.entryInfoList();
//    for (int i = 0; i < list.size(); ++i)
//    {
//       QFileInfo fileInfo = list.at(i);
//       qDebug() << qPrintable(fileInfo.fileName());
//       qDebug() << qPrintable(fileInfo.filePath());
//    }
    return (list);
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
