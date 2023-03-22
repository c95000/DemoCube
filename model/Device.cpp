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
//    rtsp://admin:ipc123456@192.168.50.85:554/h265/ch1/main/av_stream
    QString url = QString("rtsp://admin:ipc123456@%1:%2/h265/ch1/main/av_stream").arg(ip).arg(554);
    return url;
}
