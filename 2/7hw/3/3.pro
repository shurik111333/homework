#-------------------------------------------------
#
# Project created by QtCreator 2016-05-09T20:41:43
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainWidget.cpp \
    cellButton.cpp \
    ticTacToe.cpp

HEADERS  += mainWidget.h \
    cellButton.h \
    ticTacToe.h \
    ticTacToeTest.h

FORMS    += mainWidget.ui
