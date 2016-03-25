QT += testlib

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp

HEADERS += \
    priorityqueue.h \
    heap.h \
    emptyqueue.h \
    priorityqueuetest.h
