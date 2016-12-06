QT += core network sql
QT -= gui

CONFIG += c++11

TARGET = WordGameServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += src\main.cpp \
    src\Server.cpp \

HEADERS += \
    src\Server.h \
    src\Types.h

OTHER_FILES += \
    Types.json
