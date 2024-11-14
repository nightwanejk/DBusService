TEMPLATE = app
CONFIG += console c++17
QT += core dbus sql

SOURCES += \
        client.cpp \
        main.cpp \
        permissions_service.cpp \
        time_service.cpp

HEADERS += \
    client.h \
    permissions_service.h \
    time_service.h

QMAKE_EXPORT_COMPILE_COMMANDS = YES

