#-------------------------------------------------
#
# Project created by QtCreator 2014-01-03T22:17:50
#
#-------------------------------------------------

qtHaveModule(printsupport): QT += printsupport
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myconnection.cpp \
    connectionwindow.cpp

HEADERS  += mainwindow.h \
    myconnection.h \
    connectionwindow.h

FORMS    += mainwindow.ui \
    connectionwindow.ui
