QT       += core network xml
QT       -= gui

include(../use.pri)

TARGET = testConsole
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
DESTDIR=../bin

SOURCES += main.cpp \
    qexample.cpp

HEADERS += \
    qexample.h

