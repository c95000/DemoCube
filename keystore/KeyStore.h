#ifndef KEYSTORE_H
#define KEYSTORE_H

#include <QObject>
#include "Softkey.h"
#include <dbt.h>

class KeyStore : public QObject
{
    Q_OBJECT
public:
    explicit KeyStore(QObject *parent = nullptr);

    bool validate();
    int doRegisterDeviceInterface(QWidget *widget);
    SoftKey *getSoftkey();
signals:

private:
    char DevicePath[260];
    SoftKey *ytsoftkey;

    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    HDEVNOTIFY hDevNotify;

};

#endif // KEYSTORE_H
