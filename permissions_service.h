#ifndef PERMISSIONS_SERVICE_H
#define PERMISSIONS_SERVICE_H

#include <QObject>
#include <QtDBus/QtDBus>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>

enum class Permissions {
    SystemTime = 0
};

class PermissionService : public QObject {
    Q_OBJECT

public:
    explicit PermissionService(QObject *parent = nullptr);
    ~PermissionService();

public slots:
    void RequestPermission(int permissionEnumCode);
    bool CheckApplicationHasPermission(const QString &applicationExecPath, int permissionEnumCode);

private:
    QSqlDatabase db;
    void initializeDatabase();
    QString getClientExecutablePath(const QString &clientName);
    void sendErrorReply(const QString &message);
};

#endif // PERMISSIONS_SERVICE_H
