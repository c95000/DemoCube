#ifndef ARNETWRAPPER_H
#define ARNETWRAPPER_H

#include <QObject>

#include "ARNET_DATATYPE.h"
#include "ARNET_SDK.h"
#include "net_protocol.h"
#include "AR_DEFINE.h"
#include "XPlay.h"

#include "common.h"

class ArnetWrapper:public QObject
{
    Q_OBJECT
public:
    ArnetWrapper(const QString& ip);
    virtual ~ArnetWrapper();

public:
    int init();
    int release();

    QString version();

    int login();
    int logout();

    int play();
    int stop();

public:
    QString ip;
    ARNET_INIT_PARAM param;
    ARNET_LOGIN_INFO stLoginInfo;
    ARNET_DEVICE_INFO stDevicenfo;

    LONG m_lLoginHandle = -1;
    LONG m_lRealHandle = -1;
    XHANDLE m_lPlayHandle = -1;

    int m_frameWidth;
    int m_frameHeight;
};

#endif // ARNETWRAPPER_H
