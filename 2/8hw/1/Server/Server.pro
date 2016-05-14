#-------------------------------------------------
#
# Project created by QtCreator 2016-05-14T15:46:18
#
#-------------------------------------------------

QT       += core gui network

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainWidget.cpp \
    server.cpp \
    ../TcpMessenger/tcpMessenger.cpp

HEADERS  += mainWidget.h \
    server.h \
    ../TcpMessenger/tcpMessenger.h

FORMS    += mainWidget.ui
