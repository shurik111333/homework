TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    SortedSet.cpp \
    ListComparator.cpp \
    ListArray.cpp

HEADERS += \
    IList.h \
    SortedSet.h \
    ListComparator.h \
    ListArray.h

