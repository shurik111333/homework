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
    Model/Cannon/cannonSimple.cpp \
    Controllers/gameController.cpp \
    Model/Player/localplayer.cpp

HEADERS  += Views/mainwindow.h \
    Model/Landscape/iLandscapeGenerator.h \
    Model/Landscape/landscapeGeneratorFixed.h \
    Model/Cannon/icannon.h \
    Model/Cannon/cannonSimple.h \
    Controllers/gameController.h \
    Model/Player/iplayer.h \
    Model/Player/localplayer.h
