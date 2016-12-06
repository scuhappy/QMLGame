#-------------------------------------------------
#
# Project created by QtCreator 2016-12-05T11:57:08
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = WordGameServer_Asio
CONFIG   += console
CONFIG   -= app_bundle
INCLUDEPATH+= E:\\QMLGames\\boost_1_62_0
LIBS+= -LE:\QMLGames\boost_1_62_0\stage\lib
TEMPLATE = app


SOURCES += main.cpp \
    Server.cpp

HEADERS += \
    Server.h
