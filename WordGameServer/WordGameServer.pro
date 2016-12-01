QT += core network
QT -= gui

CONFIG += c++11

TARGET = WordGameServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Server.cpp \
    workthread.cpp

HEADERS += \
    Server.h \
    workthread.h \
    Types.h

OTHER_FILES += \
    Types.json
