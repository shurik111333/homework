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
    game.cpp

HEADERS  += mainWindow.h \
    gameWindow.h \
    settings.h \
    Player/iplayer.h \
    Player/localplayer.h \
    game.h

FORMS    += mainWindow.ui
