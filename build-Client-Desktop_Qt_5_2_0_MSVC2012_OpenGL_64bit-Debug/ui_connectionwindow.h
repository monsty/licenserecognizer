/********************************************************************************
** Form generated from reading UI file 'connectionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONWINDOW_H
#define UI_CONNECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectionWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *loginButton;
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ConnectionWindow)
    {
        if (ConnectionWindow->objectName().isEmpty())
            ConnectionWindow->setObjectName(QStringLiteral("ConnectionWindow"));
        ConnectionWindow->resize(300, 200);
        ConnectionWindow->setMinimumSize(QSize(300, 200));
        ConnectionWindow->setMaximumSize(QSize(300, 200));
        centralwidget = new QWidget(ConnectionWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 130, 211, 20));
        label->setAlignment(Qt::AlignCenter);
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(90, 90, 121, 32));
        loginEdit = new QLineEdit(centralwidget);
        loginEdit->setObjectName(QStringLiteral("loginEdit"));
        loginEdit->setGeometry(QRect(90, 20, 121, 21));
        passwordEdit = new QLineEdit(centralwidget);
        passwordEdit->setObjectName(QStringLiteral("passwordEdit"));
        passwordEdit->setGeometry(QRect(90, 60, 121, 21));
        ConnectionWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ConnectionWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 300, 22));
        ConnectionWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ConnectionWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ConnectionWindow->setStatusBar(statusbar);

        retranslateUi(ConnectionWindow);

        QMetaObject::connectSlotsByName(ConnectionWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ConnectionWindow)
    {
        ConnectionWindow->setWindowTitle(QApplication::translate("ConnectionWindow", "License Plate Recognizer", 0));
        label->setText(QString());
        loginButton->setText(QApplication::translate("ConnectionWindow", "Connect", 0));
        loginEdit->setText(QString());
        loginEdit->setPlaceholderText(QApplication::translate("ConnectionWindow", "Login", 0));
        passwordEdit->setText(QString());
        passwordEdit->setPlaceholderText(QApplication::translate("ConnectionWindow", "Password", 0));
    } // retranslateUi

};

namespace Ui {
    class ConnectionWindow: public Ui_ConnectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONWINDOW_H
