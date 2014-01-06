#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MyConnection *connect,
                        QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QDir dir;
    ui->setupUi(this);
    this->connection = new MyConnection();
    this->connection = connect;
    this->fileName = "";
    this->path = dir.absolutePath();
    this->fileList = dir.entryInfoList();
    this->listFileOnView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listFileOnView()
{
    QList<QTreeWidgetItem *> items;
    QStringList listName;

    ui->treeWidget->clear();
    for (int i = 0; i < this->fileList.size(); ++i)
    {
        listName.push_back(this->fileList.at(i).fileName());
        items.append(new QTreeWidgetItem((QTreeWidget*)0,
                                            QStringList(QString(listName[i]).arg(i))));
    }
    ui->treeWidget->insertTopLevelItems(0, items);
}

void MainWindow::on_pushButton_clicked()
{
    QDir        dir;
    QString     path = QFileDialog::getExistingDirectory(this,
                                                        tr("Open Directory"),
                                                        this->path,
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);

    this->path = path;
    dir.cd(path);
    this->fileList = dir.entryInfoList();
    qDebug() << path;
    this->listFileOnView();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString     fileNameToSend;

    fileNameToSend = '2' + this->fileName;
    this->connection->SendPic(fileNameToSend);
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QPixmap     pm(this->path + '/' + item->text(0));
    item;
    column;

    ui->label_2->setPixmap(pm);
    this->fileName = this->path + '/' + item->text(0);
}
