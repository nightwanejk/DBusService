#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusError>
#include <QDebug>
#include "permissions_service.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PermissionService service;

    if (!QDBusConnection::sessionBus().registerObject("/com/system/permissions", &service, QDBusConnection::ExportAllSlots)) {
        qDebug() << "Failed to register DBus object!";
        return 1;
    }

    if (!QDBusConnection::sessionBus().registerService("com.system.permissions")) {
        qDebug() << "Failed to register DBus service!";
        return 1;
    }

    qDebug() << "Service registered";
    qDebug() << "Object registered";

    return a.exec();
}
