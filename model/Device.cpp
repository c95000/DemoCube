#include "Device.h"

#include "Device.h"

Device::Device(QObject *parent)
    : QObject{parent}
{

}

Device::Device(QString ip, QString name, QObject *parent)
    : QObject{parent}, ip(ip), name(name)
{

}

Device::Device(const Device& other)
    : QObject{nullptr}
{
    ip = other.ip;
    name = other.name;
}

QString Device::getUrl() const {
    QString url = QString("rtsp://%1").arg(ip);
    return url;
}
