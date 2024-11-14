#include "time_service.h"

#include <QDateTime>
#include <QDebug>

TimeService::TimeService(PermissionService *permissionService, QObject *parent)
    : QObject(parent), permissionService(permissionService) {}

qulonglong TimeService::GetSystemTime() {
    QString clientName = QDBusConnection::sessionBus().baseService();
    QString execPath = permissionService->getClientExecutablePath(clientName);

    if (execPath.isEmpty()) {
        permissionService->sendErrorReply("com.system.time.UnknownClient",
                                          "Failed to get the executable path of the client.");
        return 0;
    }

    if (!permissionService->CheckApplicationHasPermission(execPath, static_cast<int>(Permissions::SystemTime))) {
        permissionService->sendErrorReply("com.system.time.UnauthorizedAccess",
                                          "Client does not have permission to access system time.");
        return 0;
    }

    return QDateTime::currentDateTime().toSecsSinceEpoch();
}
