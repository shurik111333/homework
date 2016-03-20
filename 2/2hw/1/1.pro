QT += testlib

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    QSort.cpp \
    HeapSort.cpp \
    BubbleSort.cpp

HEADERS += \
    ISort.h \
    QSort.h \
    HeapSort.h \
    BubbleSort.h \
    ISortTest.h

