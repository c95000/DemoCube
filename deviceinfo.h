#ifndef DEVICEINFO_H
#define DEVICEINFO_H
#include <QObject>
#include <QMutex>

class DeviceInfo: public QObject
{    
    Q_OBJECT
public:
    ~DeviceInfo();
    static DeviceInfo* GetInstance();

private:
    DeviceInfo();

    static DeviceInfo *m_instance;
    static QMutex  m_mutex;
};

//查询CPU型号
QString getCpuName();
//查询CPU核心数
QString getCpuCore();
//查询CPU线程数
QString getCpuProcessors();
//查询CPU序列号
QString getCpuProcessorid();
//查询主板序列号
QString getBaseboardSerialnumber();
//查询BIOS序列号
QString getBiosSerialnumber();
//查询主板唯一标识
QString getBaseboardUuid();
//查询硬盘序列号
QString getDiskSerialnumber();

const QString getDeviceInfo();

#endif // DEVICEINFO_H
