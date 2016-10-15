TEMPLATE = app
CONFIG += qt console c++11
CONFIG -= app_bundle
QT += testlib

SOURCES += main.cpp \
    Computer/computer.cpp \
    Network/network.cpp \
    Network/networkgeneratorcomplete.cpp \
    Virus/randomvirus.cpp \
    Virus/testvirus.cpp

HEADERS += \
    Computer/computer.h \
    Computer/os.h \
    Computer/oslinux.h \
    Computer/osmac.h \
    Computer/oswindows.h \
    Network/inetworkgenerator.h \
    Network/network.h \
    Network/networkgeneratorcomplete.h \
    Network/networktest.h \
    Virus/ivirus.h \
    Virus/randomvirus.h \
    Virus/testvirus.h
