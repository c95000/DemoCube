#include "ArnetWrapper.h"
#include "XPlay.h"
#include "Record_SDK.h"
#include <QtConcurrent/QtConcurrent>
#include <Configure.h>
#include <QFileDialog>

ArnetWrapper::ArnetWrapper()
{
    m_lLoginHandle = -1;
    m_lRealHandle = -1;
    m_lPlayHandle = -1;
    ip = "192.168.1.225";
}

ArnetWrapper::~ArnetWrapper()
{
    release();
}

BOOL ArnetWrapper::init() {
    BOOL ret = ARNET_Init(NULL);
    printf("%s ret:%d", __FUNCTION__, ret);
    if(!ret) {
        sendError(-101);
    }
    ret = login();
    printf("%s ret:%d", __FUNCTION__, ret);
    return ret;
}

BOOL ArnetWrapper::release() {
    BOOL ret = ARNET_Cleanup();
    printf("%s ret:%d", __FUNCTION__, ret);
    return ret;
}

QString ArnetWrapper::version() {
    DWORD version = ARNET_GetSDKVersions();
    QString ver = QString("version:%1.%2.%3.%4")
            .arg((version >> 24)  & 0xFF)
            .arg((version >> 16)  & 0xFF)
            .arg((version >> 8)  & 0xFF)
            .arg(version & 0xFF);
    return ver;
}

void ArnetWrapper::sendError(int errCode) {
    emit error(errCode);
}

BOOL ArnetWrapper::login() {

    memset(&stDevicenfo, 0, sizeof(ARNET_DEVICE_INFO));
    memset(&stLoginInfo, 0, sizeof(ARNET_LOGIN_INFO));

    stLoginInfo.wDevPort = 36666;
    //192.168.1.225
    strcpy(stLoginInfo.sDevIP, ip.toStdString().c_str());
    strcpy(stLoginInfo.LoginName, "admin");
    strcpy(stLoginInfo.LoginPsw, "admin");
    stLoginInfo.eMonTranMode = RTSP_DALI;

    m_lLoginHandle = ARNET_Login(stLoginInfo, &stDevicenfo, NULL, NULL, NULL, NULL);
    if (m_lLoginHandle < 0) {
        int error = ARNET_GetLastError();
        sendError(error);
        printf("%s error :%d", __FUNCTION__, error);
        return FALSE;
    }
    printf("m_lLoginHandle :%ld", m_lLoginHandle);

    return TRUE;
}

BOOL ArnetWrapper::logout() {
    BOOL ret = ARNET_LogOut(m_lLoginHandle);
    printf("%s ret:%d", __FUNCTION__, ret);
    if(!ret) {
        sendError(-102);
    }
    return ret;
}

void ArnetWrapper::connect(const QString& ip) {
    this->ip = ip;
    init();
}

void ArnetWrapper::disconnect() {
    release();
}

void ArnetWrapper::zoomWide() {
    int ret = ARNET_PtzCtrl(m_lLoginHandle, SP_ZOOM_WIDE, 0, 0);
    if (0 != ret){
        printf("zoomWide failed. errCode: %d\n", ARNET_GetLastError());
        sendError(-201);
        return;
    }
    QtConcurrent::run(this, &ArnetWrapper::zoomStop);
}

void ArnetWrapper::zoomTele() {
    int ret = ARNET_PtzCtrl(m_lLoginHandle, SP_ZOOM_TELE, 0, 0);
    if (0 != ret){
        printf("zoomTele failed. errCode: %d\n", ARNET_GetLastError());
        sendError(-202);
        return;
    }
    QtConcurrent::run(this, &ArnetWrapper::zoomStop);
}

void ArnetWrapper::zoomStop() {
    QThread::msleep(250);
    int ret = ARNET_PtzCtrl(m_lLoginHandle, SP_PTZ_STOP, 0, 0);
    if (0 != ret){
        printf("zoomTele failed. errCode: %d\n", ARNET_GetLastError());
        sendError(-203);
        return;
    }
}

