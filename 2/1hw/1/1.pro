QT += testlib

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    ListPointer.cpp \
    ListArray.cpp

HEADERS += \
    IList.h \
    ListPointer.h \
    ListArray.h \
    ListArrayTest.h \
    ListPointerTest.h

