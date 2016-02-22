TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    PrintConsole.cpp \
    PrintFile.cpp

HEADERS += \
    IPrint.h \
    PrintConsole.h \
    PrintFile.h

