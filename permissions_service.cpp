#include <QProcess>
#include <QDebug>
#include "permissions_service.h"

PermissionService::PermissionService(QObject *parent) : QObject(parent)
{
    initializeDatabase();
}

PermissionService::~PermissionService()
{
    db.close();
}

void PermissionService::initializeDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("permissions.db");

    if(!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS permissions (execPath TEXT, permissionCode INTEGER)");
}

QString PermissionService::getClientExecutablePath(const QString &clientName)
{
    // using  GetConnectionUnixProcces to get execPath
    QDBusMessage message = QDBusMessage::createMethodCall(
        "org.freedesktop.DBus", "/org/freedesktop/DBus",
        "org.freedesktop.DBus", "GetConnectionUnixProcessID");
    message << clientName;

    QDBusReply<uint> reply = QDBusConnection::sessionBus().call(message);
    if (reply.isValid()) {
        uint pid = reply.value();
        QProcess process;
        process.start("ps", QStringList() << "-p" << QString::number(pid) << "-o" << "exe=");
        process.waitForFinished();
        QString execPath = QString::fromUtf8(process.readAllStandardOutput()).trimmed();
        return execPath;
    } else {
        sendErrorReply("Failed to get PID for client " + clientName);
        return QString();
    }
}

void PermissionService::RequestPermission(int permissionEnumCode)
{
    if (permissionEnumCode != static_cast<int>(Permissions::SystemTime)) {
        sendErrorReply("Invalid permission code");
    }

    // unique client name
    QString clientName = QDBusConnection::sessionBus().baseService();

    QString execPath = getClientExecutablePath(clientName); 
    if (execPath.isEmpty()) {
        return;
    }

    // add into database
    QSqlQuery query;
    query.prepare("INSERT INTO permissions (execPath, permissionCode) VALUES (:execPath, :permissionCode)");
    query.bindValue(":execPath", execPath);  // save path
    query.bindValue(":permissionCode", permissionEnumCode);
    if (!query.exec()) {
        sendErrorReply("Error saving permission to database: " + query.lastError().text());
    }
}

bool PermissionService::CheckApplicationHasPermission(const QString &applicationExecPath, int permissionEnumCode)
{
    if (permissionEnumCode != static_cast<int>(Permissions::SystemTime)) {
        sendErrorReply("Invalid permission code");
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM permissions WHERE execPath = :execPath AND permissionCode = :permissionCode");
    query.bindValue(":execPath", applicationExecPath);
    query.bindValue(":permissionCode", permissionEnumCode);

    if (query.exec() && query.next()) {
        return true;
    }

    sendErrorReply("Permission not found for the application: " + applicationExecPath);
    return false;
}

void PermissionService::sendErrorReply(const QString &message)
{
    qDebug() << "Error:" << message;
    QDBusMessage errorMessage = QDBusMessage::createError(
        "com.system.permissions.Error",
        message
        );

    QDBusConnection::sessionBus().send(errorMessage);
}










