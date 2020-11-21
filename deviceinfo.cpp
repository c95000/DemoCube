#include "deviceinfo.h"
#include <QString>
#include <QProcess>

//获取cpu名称：wmic cpu get Name
//获取cpu核心数：wmic cpu get NumberOfCores
//获取cpu线程数：wmic cpu get NumberOfLogicalProcessors
//查询cpu序列号：wmic cpu get processorid
//查询主板序列号：wmic baseboard get serialnumber
//查询BIOS序列号：wmic bios get serialnumber
//查看硬盘：wmic diskdrive get serialnumber
//获取主板序唯一标识：wmic csproduct get uuid
//查询网卡连接唯一标识：Wmic Path Win32_NetworkAdapter get GUID
//查询网卡物理地址：Wmic Path Win32_NetworkAdapter get NetEnabled
//查询网卡是否启用：Wmic Path Win32_NetworkAdapter get NetEnabled
//查询网卡是否为物理适配器：Wmic Path Win32_NetworkAdapter get PhysicalAdapter
//查询网卡索引号：Wmic Path Win32_NetworkAdapter get Index

QString getInfo(const QString &cmd)
{
    QProcess p;				//启动外部程序
    p.start(cmd);			//一体式启动，不分离，主程序退出则启动程序退出,使用close关闭
    //p.startDetached(cmd)	//分离式启动，主程序退出后，外部程序继续运行。
    p.waitForFinished(-1);	//超时等待，设置为-1，直到执行完成。
    QString result = QString::fromLocal8Bit(p.readAllStandardOutput());
    QStringList list = cmd.split(" ");
    result = result.remove(list.last(), Qt::CaseInsensitive);
    result = result.replace("\r", "");
    result = result.replace("\n", "");
    result = result.simplified();
    p.close();
    return result;
}

DeviceInfo* DeviceInfo::m_instance = nullptr;
QMutex  DeviceInfo::m_mutex;

DeviceInfo::DeviceInfo()
{

}

DeviceInfo::~DeviceInfo()
{

}

DeviceInfo *DeviceInfo::GetInstance()
{
    if (m_instance == nullptr)
    {
        QMutexLocker locker(&m_mutex);
        if (m_instance == nullptr)
        {
            m_instance = new DeviceInfo();
        }
    }
    return m_instance;
}

//查询CPU型号
QString getCpuName()
{
    return getInfo("wmic cpu get Name");
}
//查询CPU核心数
QString getCpuCore()
{
    return getInfo("wmic cpu get NumberOfCores");
}
//查询CPU线程数
QString getCpuProcessors()
{
    return getInfo("wmic cpu get NumberOfLogicalProcessors");
}
//查询CPU序列号
QString getCpuProcessorid()
{
     return getInfo("wmic cpu get processorid");
}
//查询主板序列号
QString getBaseboardSerialnumber()
{
     return getInfo("wmic baseboard get serialnumber");
}
//查询BIOS序列号
QString getBiosSerialnumber()
{
     return getInfo("wmic bios get serialnumber");
}
//查询主板唯一标识
QString getBaseboardUuid()
{
     return getInfo("wmic csproduct get uuid");
}
//查询硬盘序列号
QString getDiskSerialnumber()
{
     return getInfo("wmic diskdrive get serialnumber");
}
