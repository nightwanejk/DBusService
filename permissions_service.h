#ifndef PERMISSIONS_SERVICE_H
#define PERMISSIONS_SERVICE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QtDBus/QtDBus>

enum class Permissions { SystemTime = 0 };

class PermissionService : public QObject {
    Q_OBJECT

   public:
    explicit PermissionService(QObject *parent = nullptr);
    ~PermissionService();
    void sendErrorReply(const QString &errorName, const QString &message);
    QString getClientExecutablePath(const QString &clientName);

   public slots:
    void RequestPermission(int permissionEnumCode);
    bool CheckApplicationHasPermission(const QString &applicationExecPath, int permissionEnumCode);

   private:
    QSqlDatabase db;
    void initializeDatabase();
};

#endif  // PERMISSIONS_SERVICE_H
