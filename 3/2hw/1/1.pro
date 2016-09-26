TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    network.cpp \
    computer.cpp \
    networkgeneratorcomplete.cpp

HEADERS += \
    network.h \
    os.h \
    oswindows.h \
    oslinux.h \
    osmac.h \
    computer.h \
    inetworkgenerator.h \
    networkgeneratorcomplete.h
