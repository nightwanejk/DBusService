#ifndef CLIENT_H
#define CLIENT_H

#include <QCoreApplication>
#include <QObject>
#include <QtDBus/QtDBus>

#include "permissions_service.h"

class TimeClient : public QObject {
    Q_OBJECT

   public:
    explicit TimeClient(QObject *parent = nullptr);
    void requestTime();

   private:
    QDBusInterface *timeInterface;
    QDBusInterface *permissionInterface;
    void requestPermission(int permissionCode);

   public slots:
    void onTimeReceived(qulonglong timestamp);
};

#endif  // CLIENT_H
