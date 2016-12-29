#-------------------------------------------------
#
# Project created by QtCreator 2016-12-22T15:57:43
#
#-------------------------------------------------

QT       += core gui network

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
    Tank/tankSimple.cpp \
    Player/networkplayer.cpp \
    TcpMessenger/tcpMessenger.cpp \
    Server/server.cpp \
    Player/localplayerproxy.cpp \
    Shell/shellExplosive.cpp \
    Shell/ShellType/standart.cpp \
    Shell/ShellType/explosive.cpp \
    Shell/Explosion/explosion.cpp

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
    Tank/tankSimple.h \
    Player/networkplayer.h \
    TcpMessenger/tcpMessenger.h \
    Server/server.h \
    Player/localplayerproxy.h \
    action.h \
    Shell/shellExplosive.h \
    Shell/ShellType/ishelltype.h \
    Shell/ShellType/standart.h \
    Shell/ShellType/explosive.h \
    Shell/Explosion/explosion.h

FORMS    += mainWindow.ui

RESOURCES += \
    Resources/sprites.qrc

DISTFILES +=
