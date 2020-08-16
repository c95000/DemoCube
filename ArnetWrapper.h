#ifndef ARNETWRAPPER_H
#define ARNETWRAPPER_H

#include <QObject>

#include "ARNET_DATATYPE.h"
#include "ARNET_SDK.h"
#include "net_protocol.h"
#include "AR_DEFINE.h"
#include "XPlay.h"

#include "VideoRenderCallback.h"
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

    BOOL deepPlay();
    BOOL deepStop();

signals:
    void started();
    void paused();
    void stopped();
    void error(QString& err);

public:
    QString version();

    int start(const QString& ip, VideoRenderCallback* renderCb);
    int playFile(const QString& fileName, VideoRenderCallback* renderCb);
    int play();
    int stop();
    void resume();
    void pause();
    void toggle();
    bool isWorking();
    bool isPlaying();

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

    VideoRenderCallback* renderCallback;
    bool isPlay;
};

#endif // ARNETWRAPPER_H
