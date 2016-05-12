#-------------------------------------------------
#
# Project created by QtCreator 2016-05-12T11:30:10
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainWidget.cpp \
    bash.cpp

HEADERS  += mainWidget.h \
    bash.h

FORMS    += mainWidget.ui
