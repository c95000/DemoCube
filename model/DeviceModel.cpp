#include "DeviceModel.h"

DeviceModel::DeviceModel(QObject *parent)
    : QObject{parent}
{

}

void DeviceModel::addOne(Device& device) {
    deviceList.append(device);
    emit dataChanged();
}

void DeviceModel::removeOne(const Device device) {
    deviceList.removeOne(device);
    emit dataChanged();
}

QList<Device>& DeviceModel::getDeviceList() {
    return deviceList;
}

Device::Device(QString ip, QString name) {
    this->ip = ip;
    this->name = name;
}

Device::Device(const Device& copy) {
    this->ip = copy.ip;
    name = copy.name;
}

QString Device::getUrl() {
    QString url = QString("rtsp://%1").arg(ip);
    return url;
}
