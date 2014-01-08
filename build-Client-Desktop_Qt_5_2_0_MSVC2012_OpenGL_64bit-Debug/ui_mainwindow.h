/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTreeWidget *treeWidget;
    QPushButton *selectDirectory;
    QPushButton *recognize;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *preview;
    QLabel *actualfile;
    QCheckBox *checkBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(700, 449);
        MainWindow->setMinimumSize(QSize(700, 449));
        MainWindow->setMaximumSize(QSize(700, 449));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        treeWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setTextAlignment(0, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(470, 20, 211, 351));
        selectDirectory = new QPushButton(centralWidget);
        selectDirectory->setObjectName(QStringLiteral("selectDirectory"));
        selectDirectory->setGeometry(QRect(270, 270, 114, 32));
        recognize = new QPushButton(centralWidget);
        recognize->setObjectName(QStringLiteral("recognize"));
        recognize->setGeometry(QRect(70, 270, 114, 32));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(220, 350, 113, 21));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 350, 111, 21));
        preview = new QLabel(centralWidget);
        preview->setObjectName(QStringLiteral("preview"));
        preview->setGeometry(QRect(10, 10, 441, 231));
        preview->setScaledContents(true);
        preview->setAlignment(Qt::AlignCenter);
        actualfile = new QLabel(centralWidget);
        actualfile->setObjectName(QStringLiteral("actualfile"));
        actualfile->setGeometry(QRect(20, 320, 431, 20));
        actualfile->setAlignment(Qt::AlignCenter);
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(510, 380, 141, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(selectDirectory, SIGNAL(clicked()), preview, SLOT(show()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "License Plate Recognizer", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "File", 0));
        selectDirectory->setText(QApplication::translate("MainWindow", "Select Folder", 0));
        recognize->setText(QApplication::translate("MainWindow", "Recognize", 0));
        lineEdit->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Plate Number :", 0));
        preview->setText(QApplication::translate("MainWindow", "no image selected", 0));
        actualfile->setText(QString());
        checkBox->setText(QApplication::translate("MainWindow", "Automatic upload", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
