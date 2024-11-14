#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusError>
#include <QDebug>

#include "client.h"
#include "permissions_service.h"
#include "time_service.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    PermissionService service;

    if (!QDBusConnection::sessionBus().registerService("com.system.permissions")) {
        qDebug() << "Failed to register PermissionService DBus service!";
        return 1;
    }

    if (!QDBusConnection::sessionBus().registerObject("/com/system/permissions", &service,
                                                      QDBusConnection::ExportAllSlots)) {
        qDebug() << "Failed to register PermissionService DBus object!";
        return 1;
    }
    qDebug() << "PermissionService registered";

    TimeService timeService(&service);

    if (!QDBusConnection::sessionBus().registerService("com.system.time")) {
        qDebug() << "Failed to register TimeService DBus service!";
        return 1;
    }

    if (!QDBusConnection::sessionBus().registerObject("/com/system/time", &timeService,
                                                      QDBusConnection::ExportAllSlots)) {
        qDebug() << "Failed to register TimeService DBus object!";
        return 1;
    }
    qDebug() << "TimeService registered";

    TimeClient client;
    client.requestTime();

    return a.exec();
}
