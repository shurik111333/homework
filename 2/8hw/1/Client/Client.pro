#-------------------------------------------------
#
# Project created by QtCreator 2016-05-14T18:56:58
#
#-------------------------------------------------

QT       += core gui network
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainWidget.cpp \
    client.cpp

HEADERS  += mainWidget.h \
    client.h

FORMS    += mainWidget.ui
