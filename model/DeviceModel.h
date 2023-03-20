#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>
#include <QAbstractItemModel>

class Device : public QObject{
    Q_OBJECT
public:
    explicit Device(QString ip, QString name = nullptr);
    explicit Device(const Device& copy);
    QString getUrl();

    Device& operator=(Device& r)
    {
        ip = r.ip;
        name = r.name;
        return *this;
    }

    bool operator==(const Device &a) const
    {
        return a.ip == ip;
    }

    bool operator<(const Device &a) const
    {
        return ip < a.ip;
    }
    QString ip;
    QString name;
};

class DeviceModel : public QObject
{
    Q_OBJECT
public:
    explicit DeviceModel(QObject *parent = nullptr);

    //    QString& getIp();
    //    QString& getName();
    //    QString getUrl();

    void addOne(Device& device);
    void removeOne(const Device device);
    QList<Device>& getDeviceList();
signals:
    void dataChanged();

private:
    QList<Device> deviceList;
};

#endif // DEVICEMODEL_H
