QT += core network
QT -= gui

CONFIG += c++11

TARGET = WordGameServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += src\main.cpp \
    src\Server.cpp \
    src\workthread.cpp

HEADERS += \
    src\Server.h \
    src\workthread.h \
    src\Types.h

OTHER_FILES += \
    Types.json
