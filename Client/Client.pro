#-------------------------------------------------
#
# Project created by QtCreator 2014-01-03T22:17:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myconnection.cpp

HEADERS  += mainwindow.h \
    myconnection.h

FORMS    += mainwindow.ui
