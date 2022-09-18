#include "KeyStore.h"
#include <QMessageBox>
#include <dbt.h>
#include <QDebug>

KeyStore::KeyStore(QObject *parent)
    : QObject{parent}
{
    ytsoftkey=new SoftKey();
    if(!ytsoftkey->IsLoad)
    {
         QMessageBox::critical(NULL, QStringLiteral("错误"),QStringLiteral("加载类DLL时错误。"), QMessageBox::Close);
         exit(0);
    }
    //这个用于判断系统中是否存在着加密锁。不需要是指定的加密锁,
   if (ytsoftkey->FindPort(0, DevicePath) != 0)
   {
       QMessageBox::critical(NULL, QStringLiteral("错误"),QStringLiteral("未找到加密锁,请插入加密锁后，再进行操作。"), QMessageBox::Close);
        exit(0);
   }
//   if(!DoRegisterDeviceInterface()) {
//       QMessageBox::critical(NULL, QStringLiteral("错误"), QStringLiteral("注册事件通知失败。"), QMessageBox::Close);
//   }
}

bool KeyStore::validate() {
    return true;
}

int KeyStore::doRegisterDeviceInterface(QWidget *widget)
{
  GUID hid_guid={0x4D1E55B2,0xF16F,0x11CF,0x88,0xCB,0x00,0x11,0x11,0x00,0x00,0x30
                };
  DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;

  ZeroMemory( &NotificationFilter, sizeof(NotificationFilter) );
  NotificationFilter.dbcc_size =
      sizeof(DEV_BROADCAST_DEVICEINTERFACE);
  NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
  NotificationFilter.dbcc_classguid = hid_guid;
  hDevNotify = RegisterDeviceNotification((HWND*)widget->winId(),
                                          &NotificationFilter,
                                          DEVICE_NOTIFY_WINDOW_HANDLE
                                          );

  if(!hDevNotify)
    {
      return false;
    }

  return true;
}

SoftKey *KeyStore::getSoftkey() {
    return ytsoftkey;
}

bool KeyStore::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
  Q_UNUSED(result);
  Q_UNUSED(eventType);

  MSG *msg = static_cast<MSG*>(message);
  qDebug() << msg;
  if(msg->message == WM_DEVICECHANGE)
    {
      qDebug() << "wParam: " << QString::number(msg->wParam, 16);
      switch (msg->wParam)
        {
        PDEV_BROADCAST_HDR broadcastHdr;

        case DBT_DEVICEARRIVAL:

          broadcastHdr = (PDEV_BROADCAST_HDR) msg->lParam;

          if (DBT_DEVTYP_DEVICEINTERFACE == broadcastHdr -> dbch_devicetype)
            {
              if(ytsoftkey->CheckKeyByFindort_2()==0)  QMessageBox::critical(NULL, QStringLiteral("警告"),QStringLiteral("加密锁被插入。"), QMessageBox::Close);
            }
          break;

        case DBT_DEVICEREMOVEPENDING:
        case DBT_DEVICEREMOVECOMPLETE://收到硬件拨出信息后，调用检查锁函数来检查是否锁被拨出
          {
            //这里使用 CheckKeyByFindort_2检查加密锁是否被拨出，也可以使用其它检查锁函数来检查加密锁是否被拨出
            if(ytsoftkey->CheckKeyByFindort_2()!=0)
            {
                  QMessageBox::critical(NULL, QStringLiteral("警告"),QStringLiteral("加密锁被拨出。"), QMessageBox::Close);
                  exit(0);
            }
          }
          break;

        default:
          break;
        }
    }
  return false;
}
