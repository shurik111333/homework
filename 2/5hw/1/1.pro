QT += testlib

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    tree.cpp

HEADERS += \
    tree.h \
    testTree.h
