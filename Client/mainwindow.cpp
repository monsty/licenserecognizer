#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MyConnection *connect,
                        QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QStringList listName;
    QList<QTreeWidgetItem *> items;
    QDir dir;
    ui->setupUi(this);
    this->connection = new MyConnection();
    this->connection = connect;
    this->fileName = "";
    this->path = dir.absolutePath();
    this->fileList = dir.entryInfoList();
    for (int i = 0; i < this->fileList.size(); ++i)
    {
        listName.push_back(this->fileList.at(i).fileName());
        items.append(new QTreeWidgetItem((QTreeWidget*)0,
                                            QStringList(QString(listName[i]).arg(i))));
    }
    ui->treeWidget->insertTopLevelItems(0, items);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
/*    this->fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.bmp *.jpg)"));
    QStringList parts = fileName.split("/");
    QPixmap pm(fileName);

    ui->label_3->setText(parts.at(parts.size() - 1));*/
}

void MainWindow::on_pushButton_2_clicked()
{
    QString     fileNameToSend;

    fileNameToSend = this->fileName;
    this->connection->SendPic(fileNameToSend);
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QPixmap     pm(this->path + '/' + item->text(0));
    item;
    column;

    ui->label_2->setPixmap(pm);
    this->fileName = this->path + "/" + item->text(0);
    qDebug() << "test :::    " << this->fileName;
}
