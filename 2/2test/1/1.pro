QT += testlib core

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp

HEADERS += \
    bubbleSorter.h \
    comparator.h \
    bubbleSorterTest.h \
    intComparator.h

DISTFILES +=
