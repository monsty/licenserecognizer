#-------------------------------------------------
#
# Project created by QtCreator 2014-01-03T22:17:50
#
#-------------------------------------------------

<<<<<<< HEAD
QT       += core gui
qtHaveModule(printsupport): QT += printsupport
=======
QT       += core gui network
>>>>>>> af70f31ef49a4d805050d405ff77c53070d15f78

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myconnection.cpp

HEADERS  += mainwindow.h \
    myconnection.h

FORMS    += mainwindow.ui
