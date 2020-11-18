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
    ArnetWrapper();
    virtual ~ArnetWrapper();

private:
    BOOL init();
    BOOL release();
    BOOL login();
    BOOL logout();
    void zoomStop();
    QString version();

    void sendError(int errCode);

signals:
    void error(int);

public slots:
    void connect(const QString&);
    void disconnect();
    void zoomWide();
    void zoomTele();

public:
    QString ip;
    ARNET_INIT_PARAM param;
    ARNET_LOGIN_INFO stLoginInfo;
    ARNET_DEVICE_INFO stDevicenfo;

    LONG m_lLoginHandle = -1;
    LONG m_lRealHandle = -1;
    XHANDLE m_lPlayHandle = -1;

    LONG m_lRecordHandle = -1;

};

#endif // ARNETWRAPPER_H
