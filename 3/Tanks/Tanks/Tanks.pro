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
    Model/Landscape/landscapeGeneratorFixed.cpp \
    Controllers/gameController.cpp \
    Model/Player/localplayer.cpp \
    Model/Landscape/ilandscapegenerator.cpp \
    Model/Tank/tankSimple.cpp \
    Model/Shell/shellStandart.cpp \
    Model/Shell/abstractShell.cpp \
    Model/Tank/abstractTank.cpp

HEADERS  += Views/mainwindow.h \
    Model/Landscape/iLandscapeGenerator.h \
    Model/Landscape/landscapeGeneratorFixed.h \
    Controllers/gameController.h \
    Model/Player/iplayer.h \
    Model/Player/localplayer.h \
    Model/Tank/tankSimple.h \
    Model/Shell/shellStandart.h \
    Model/Shell/abstractShell.h \
    Model/Tank/abstractTank.h
