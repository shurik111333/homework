#-------------------------------------------------
#
# Project created by QtCreator 2016-12-22T15:57:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tanks
TEMPLATE = app


SOURCES += main.cpp\
        mainWindow.cpp \
    gameWindow.cpp \
    settings.cpp \
    Player/localplayer.cpp \
    game.cpp \
    Landscape/ilandscapegenerator.cpp \
    Landscape/landscapeGeneratorFixed.cpp \
    Shell/ishell.cpp \
    Shell/shellStandart.cpp \
    Tank/iTank.cpp \
    Tank/tankSimple.cpp

HEADERS  += mainWindow.h \
    gameWindow.h \
    settings.h \
    Player/iplayer.h \
    Player/localplayer.h \
    game.h \
    Landscape/iLandscapeGenerator.h \
    Landscape/landscapeGeneratorFixed.h \
    Shell/ishell.h \
    Shell/shellStandart.h \
    Tank/iTank.h \
    Tank/tankSimple.h

FORMS    += mainWindow.ui
