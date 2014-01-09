#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QMainWindow>
#include "mainwindow.h"

namespace Ui {
class ServerConnection;
}

class ServerConnection : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerConnection(QWidget *parent = 0);
    ~ServerConnection();

private slots:
    void on_loginButton_clicked();

private:
    Ui::ServerConnection    *ui;
    MainWindow              *mainWindow;
};

#endif // SERVERCONNECTION_H
