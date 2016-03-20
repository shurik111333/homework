QT += testlib

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    PrintConsole.cpp \
    PrintFile.cpp \
    PrintMatrix.cpp

HEADERS += \
    IPrint.h \
    PrintConsole.h \
    PrintFile.h \
    PrintMatrixTest.h \
    PrintMatrix.h

