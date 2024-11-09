TEMPLATE = app
CONFIG += console c++17
QT += core dbus sql

SOURCES += \
        main.cpp \
        permissions_service.cpp

HEADERS += \
    common.h \
    permissions_service.h
