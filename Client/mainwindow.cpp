#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MyConnection *connect, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connection(connect)
{
    QDir dir;

    ui->setupUi(this);
    this->path = dir.absolutePath();
    this->fileName = "";
    this->fileList = dir.entryInfoList();
    this->listFileOnView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFileList()
{
    QDir dir;

    dir.cd(this->path);
    this->fileList = dir.entryInfoList();
}

void MainWindow::listFileOnView()
{
    QList<QTreeWidgetItem *> items;
    QStringList listName;

    ui->treeWidget->clear();
    for (int i = 0; i < this->fileList.size(); ++i)
    {
        listName.push_back(this->fileList.at(i).fileName());
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(listName[i]).arg(i))));
    }
    ui->treeWidget->insertTopLevelItems(0, items);
}

void MainWindow::on_selectDirectory_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), this->path,
                                                     QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    this->path = path;
    this->updateFileList();
    this->listFileOnView();
}

void MainWindow::on_recognize_clicked()
{
    this->connection->SendPic(this->fileName);
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QPixmap     pm(this->path + '/' + item->text(0));

    if (column == 0)
    {
        ui->label_2->setPixmap(pm);
        this->fileName = this->path + "/" + item->text(0);
    }
}
