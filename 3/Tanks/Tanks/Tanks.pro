#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T14:03:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tanks
TEMPLATE = app


SOURCES += main.cpp\
        Views/mainwindow.cpp \
    Controllers/landscapeGeneratorFixed.cpp \
    Controllers/mainwindowController.cpp

HEADERS  += Views/mainwindow.h \
    Controllers/iLandscapeGenerator.h \
    Controllers/landscapeGeneratorFixed.h \
    Controllers/mainwindowController.h
