#-------------------------------------------------
#
# Project created by QtCreator 2014-01-03T23:03:45
#
#-------------------------------------------------

QT       += core gui network sql

mac: CONFIG += MAC_CONFIG

MAC_CONFIG {
    CONFIG   += c++11
    QMAKE_CXXFLAGS += -stdlib=libc++
    QMAKE_CXXFLAGS += -mmacosx-version-min=10.7
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    server.cpp \
    database.cpp \
    myclient.cpp \
    logintask.cpp \
    getpictask.cpp \
    serverconnection.cpp \
    platedetector.cpp

HEADERS  += mainwindow.h \
    server.h \
    database.h \
    myclient.h \
    logintask.h \
    getpictask.h \
    serverconnection.h \
    platedetector.h

FORMS    += mainwindow.ui \
    serverconnection.ui

unix: INCLUDEPATH += /usr/local/include \
                    /opt/local/include

#OpenCV Library
unix: LIBS += -L/usr/local/lib \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgproc \
    -lopencv_legacy \
    -lopencv_contrib \
    -lopencv_calib3d \
    -lopencv_features2d \
    -lopencv_flann \
    -lopencv_ml \
    -lopencv_objdetect \
    -lopencv_video

#Tesseract Library
unix: LIBS += -L/opt/local/lib -ltesseract
unix: LIBS += -L/opt/local/lib -llept

