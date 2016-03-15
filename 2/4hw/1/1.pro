#-------------------------------------------------
#
# Project created by QtCreator 2016-03-12T20:12:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 1
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainWidget.cpp \
    settingsWidget.cpp \
    hashmap.cpp \
    polyhash.cpp \
    settings.cpp \
    linearhash.cpp

HEADERS  += mainWidget.h \
    settingsWidget.h \
    hashmap.h \
    ihash.h \
    polyhash.h \
    settings.h \
    linearhash.h

FORMS    += mainWidget.ui \
    settingsWidget.ui
