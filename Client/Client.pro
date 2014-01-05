#-------------------------------------------------
#
# Project created by QtCreator 2014-01-03T22:17:50
#
#-------------------------------------------------

QT       += core gui
qtHaveModule(printsupport): QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageviewer.cpp

HEADERS  += mainwindow.h \
    imageviewer.h

FORMS    += mainwindow.ui
