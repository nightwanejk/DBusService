#ifndef TIME_SERVICE_H
#define TIME_SERVICE_H

#include <QObject>
#include <QString>
#include <QtDBus/QtDBus>

#include "permissions_service.h"

class TimeService : public QObject {
    Q_OBJECT

   public:
    explicit TimeService(PermissionService *permissionService, QObject *parent = nullptr);

   public slots:
    qulonglong GetSystemTime();

   private:
    PermissionService *permissionService;
};

#endif  // TIME_SERVICE_H
