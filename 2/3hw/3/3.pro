#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T12:29:33
#
#-------------------------------------------------

QT       += core gui
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        MainWindow.cpp \
    Calculator.cpp \
    Lexer.cpp

HEADERS  += MainWindow.h \
    Calculator.h \
    IStack.h \
    StackArray.h \
    calculatortest.h

FORMS    += MainWindow.ui

DISTFILES +=
