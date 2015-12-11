#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T20:16:43
#
#-------------------------------------------------

QT       -= gui

TARGET = list
TEMPLATE = lib

DEFINES += LIST_LIBRARY

SOURCES += list.cpp

HEADERS += list.h\
        list_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
