#include "client.h"

#include <QDateTime>
#include <QDebug>

TimeClient::TimeClient(QObject *parent) : QObject(parent) {
    timeInterface = new QDBusInterface("com.system.time", "/com/system/time", "local.DBusService.TimeService",
                                       QDBusConnection::sessionBus(), this);
    permissionInterface =
        new QDBusInterface("com.system.permissions", "/com/system/permissions", "local.DBusService.PermissionService",
                           QDBusConnection::sessionBus(), this);
}

void TimeClient::requestTime() {
    if (timeInterface->isValid()) {
        qDebug() << "Requesting time from service...";
        QDBusReply<qulonglong> reply = timeInterface->call("GetSystemTime");

        if (reply.isValid()) {
            qulonglong timestamp = reply.value();
            onTimeReceived(timestamp);
        } else {
            if (reply.error().name() == "com.system.time.UnauthorizedAccess") {
                qDebug() << "Unauthorized access to system time. Requesting permission...";
                requestPermission(static_cast<int>(Permissions::SystemTime));  // Указываем тип разрешения
            } else {
                qDebug() << "Failed to get time:" << reply.error().message();
            }
        }
    } else {
        qDebug() << "Time service interface is not valid!";
    }
}

void TimeClient::onTimeReceived(qulonglong timestamp) {
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(timestamp);
    qDebug() << "Current system time:" << dateTime.toString();
}

void TimeClient::requestPermission(int permissionCode) {
    qDebug() << "Requesting permission to access system time...";

    QString execPath = QCoreApplication::applicationFilePath();

    if (permissionInterface->isValid()) {
        QDBusReply<void> reply = permissionInterface->call("RequestPermission", execPath, permissionCode);

        if (reply.isValid()) {
            qDebug() << "Permission granted. Retrying to request time...";
            requestTime();
        } else {
            qDebug() << "Permission request failed:" << reply.error().message();
        }
    } else {
        qDebug() << "Permission service interface is not valid!";
    }
}
