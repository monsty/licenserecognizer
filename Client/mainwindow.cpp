#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MyConnection *connect_cpy, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connection(connect_cpy)
{
    ui->setupUi(this);

    this->selectedFile = "";
    this->directoryPath = "";
    this->updateFileList();
    this->listFileOnView();

    connect(ui->treeWidget->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(myTreeSelectionChanged(const QItemSelection &)));

    this->autoScan = new QTimer();
    this->autoScan->connect(this->autoScan, SIGNAL(timeout()), this, SLOT(directoryRefresh()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFileList()
{
    QFileInfoList tmp_list;
    QDir dir;

    if (this->directoryPath == "")
        this->directoryPath = dir.absolutePath();

    this->fileList.clear();
    dir.cd(this->directoryPath);
    tmp_list = dir.entryInfoList();
    for (int i = 0; i < tmp_list.size(); ++i)
    {
        QString tmp_name = tmp_list.at(i).fileName();
        if (tmp_name.endsWith(".jpg", Qt::CaseInsensitive) == 1 ||
            tmp_name.endsWith(".bmp", Qt::CaseInsensitive) == 1 ||
            tmp_name.endsWith(".png", Qt::CaseInsensitive) == 1)
        {
            MyFile new_file;
            new_file.name = tmp_list.at(i).fileName();
            new_file.sent = false;
            new_file.path = this->directoryPath;
            new_file.plate = "";
            this->fileList.push_back(new_file);
        }
    }
}

void MainWindow::listFileOnView()
{
    QList<QTreeWidgetItem *> items;

    ui->treeWidget->clear();
    for (int i = 0; i < this->fileList.size(); ++i)
    {
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(this->fileList.at(i).name))));
    }
    ui->treeWidget->insertTopLevelItems(0, items);
}

void MainWindow::on_selectDirectory_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), this->directoryPath,
                                                     QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (path != "")
    {
        this->directoryPath = path;
        this->updateFileList();
        this->listFileOnView();
    }
}

void MainWindow::on_recognize_clicked()
{
    this->connection->SendPic(this->selectedFile);
}

void MainWindow::on_checkBox_stateChanged(int state)
{
    if (state == 2)
    {
        ui->recognize->setEnabled(false);
        ui->selectDirectory->setEnabled(false);
        this->autoScan->start(1000);
    }
    else
    {
        ui->recognize->setEnabled(true);
        ui->selectDirectory->setEnabled(true);
        this->autoScan->stop();
    }
}

void MainWindow::myTreeSelectionChanged(const QItemSelection & selected)
{
    if (selected.size())
    {
        MyFile file = this->fileList.at(selected.indexes().at(0).row());
        QPixmap pm(file.path+ '/' + file.name);

        ui->preview->setPixmap(pm);
        ui->actualfile->setText(file.name);
        this->selectedFile = file.path + "/" + file.name;
    }
    else
    {
        ui->preview->clear();
        ui->actualfile->setText("");
        this->selectedFile = "";
    }
}

void MainWindow::directoryRefresh()
{
    qDebug() << "Temporary refresh";
}
