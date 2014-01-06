#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "myconnection.h"

namespace Ui {
class ConnectionWindow;
}

class ConnectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnectionWindow(QWidget *parent = 0);
    ~ConnectionWindow();

private slots:
    void on_loginButton_clicked();

private:
    Ui::ConnectionWindow    *ui;
    MainWindow              *mainWindow;
    MyConnection            *connection;
};

#endif // CONNECTIONWINDOW_H
