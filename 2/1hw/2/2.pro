QT += testlib

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    Calculator.cpp \
    Lexer.cpp

HEADERS += \
    IStack.h \
    StackPointer.h \
    StackArray.h \
    Calculator.h \
    stackarraytest.h \
    stackpointertest.h \
    calculatortest.h

