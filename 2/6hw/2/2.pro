QT += testlib

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    UniqueList.cpp

HEADERS += \
    UniqueList.h \
    UniqueListTest.h
