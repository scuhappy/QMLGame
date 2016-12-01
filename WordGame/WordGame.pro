QT += qml quick

CONFIG += c++11

SOURCES += src/main.cpp \
    src/Tools.cpp \
    src/Client.cpp \
    src/Logical.cpp \
    src/Model.cpp \
    src/WriteWorker.cpp \
    src/ReadWorker.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/Tools.h \
    src/Client.h \
    src/Logical.h \
    src/Model.h \
    src/WriteWorker.h \
    src/ReadWorker.h \
    src/Types.h
