#-------------------------------------------------
#
# Project created by QtCreator 2015-05-25T01:28:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SEG2106
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcpserver.cpp \
    tcpsocket.cpp \
    thread.cpp \
    tableitem.cpp \
    linegraphwidget.cpp

HEADERS  += mainwindow.h \
    thread.h \
    tcpserver.h \
    tcpsocket.h \
    tableitem.h \
    linegraphwidget.h

FORMS    += mainwindow.ui
