#-------------------------------------------------
#
# Project created by QtCreator 2014-01-03T23:03:45
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp \
    database.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    server.h \
    database.h \
    mythread.h

FORMS    += mainwindow.ui
