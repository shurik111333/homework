TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += testlib

SOURCES += main.cpp \
    Computer/computer.cpp \
    Network/network.cpp \
    Network/networkgeneratorcomplete.cpp \
    Virus/randomvirus.cpp \
    Tests/testvirus.cpp

HEADERS += \
    Computer/computer.h \
    Computer/os.h \
    Computer/oslinux.h \
    Computer/osmac.h \
    Computer/oswindows.h \
    Network/inetworkgenerator.h \
    Network/network.h \
    Network/networkgeneratorcomplete.h \
    Virus/ivirus.h \
    Virus/randomvirus.h \
    Tests/networktest.h \
    Tests/testvirus.h \
    Tests/testnetworkgenerator.h
