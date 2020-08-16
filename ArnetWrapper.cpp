#include "ArnetWrapper.h"
#include "XPlay.h"

ArnetWrapper::ArnetWrapper():isPlay(false)
{
    m_lLoginHandle = -1;
    m_lRealHandle = -1;
    m_lPlayHandle = -1;
    init();
}

ArnetWrapper::~ArnetWrapper()
{
}

void WINAPI RealDataCallBack(LONG lRealHandle, char *pBuffer, DWORD dwBufSize, ARNET_FRAME_INFO *pFrameInfo, void* pUser) {
//    printf("%s lRealHandle:%ld pBuffer:%p bufSize:%ld data:%p", __FUNCTION__,
//           lRealHandle, pBuffer, dwBufSize, pUser);
    ArnetWrapper *arnetWrapper=(ArnetWrapper*)pUser;

    UINT64 u64Time = 0;
    u64Time = (UINT64)pFrameInfo->secCapTime * 1000 + pFrameInfo->usecCapTime / 1000;

    if (arnetWrapper->m_lPlayHandle >= 0){
        X_VideoInputData2(arnetWrapper->m_lPlayHandle, (BYTE*)pBuffer, dwBufSize, u64Time);
    }
    else
    {
        printf("eeeeeeeeeeeeee123\n");
    }
}

void CALLBACK DecodeCBFun(int handle,
                char  *pBuf,
                LONG  nSize,
                X_FRAME_INFO  *pFrameInfo,
                void*  pUser,
                LONG  nReserved1)
{
    printf("%s handle:%d pBuf:%p nSize:%ld pUser：%p", __FUNCTION__, handle, pBuf, nSize, pUser);
//    printf("%s pFrameInfo: %ld %ld %ld %ld %ld", __FUNCTION__,
//           pFrameInfo->nType, pFrameInfo->nStamp,
//           pFrameInfo->nWidth, pFrameInfo->nHeight, pFrameInfo->nFrameRate);

    ArnetWrapper *arnetWrapper=(ArnetWrapper*)pUser;
    if(NULL != arnetWrapper->renderCallback) {
        arnetWrapper->renderCallback->renderYUV((uchar*)pBuf, nSize, pFrameInfo->nWidth, pFrameInfo->nHeight, 0);
    }
}

BOOL ArnetWrapper::init() {
    BOOL ret = ARNET_Init(NULL);
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
        printf("%s error :%d", __FUNCTION__, error);
        return FALSE;
    }
    printf("m_lLoginHandle :%ld", m_lLoginHandle);

    return TRUE;
}

BOOL ArnetWrapper::logout() {
    BOOL ret = ARNET_LogOut(m_lLoginHandle);
    printf("%s ret:%d", __FUNCTION__, ret);
    return ret;
}

BOOL ArnetWrapper::deepPlay() {

}

BOOL ArnetWrapper::deepStop() {

}

int ArnetWrapper::start(const QString& ip, VideoRenderCallback* renderCb) {
    this->renderCallback = renderCb;
    this->ip = ip;

    if(ip.isNull() || ip.isEmpty()) {
        return -1;
    }

    if(!login()) {
        return -1;
    }

    int ret = play();
    return ret;
}

int ArnetWrapper::playFile(const QString& fileName, VideoRenderCallback* renderCb) {

}

int ArnetWrapper::play() {
    m_lPlayHandle = X_OpenStream2(X_STREAM_REALTIME, X_Draw_Balanced, X_DECTYPE_DEFAULT);

    m_lRealHandle = ARNET_StartRealPlay(m_lLoginHandle, 0, MBT_VIDEOPS, RealDataCallBack, this);
    if (m_lRealHandle < 0)
    {
        printf("请求主码流失败! 错误码为: %d\n", ARNET_GetLastError());
        return -1;
    }

    //窗口句柄设为null时才会回调yuv数据
    X_PlayEx(m_lPlayHandle, nullptr);

    //设置yuv数据回调
    BOOL bRet = X_SetVisibleDecCallBack(m_lPlayHandle, DecodeCBFun, (void*)this);
    if (bRet == FALSE) {
        printf("error\n");
        return -1;
    }
    isPlay = true;
    emit started();
    return 1;
}

int ArnetWrapper::stop() {
    isPlay = false;
    BOOL ret = ARNET_StopRealPlay(m_lRealHandle);
    m_lRealHandle = -1;
    m_lPlayHandle = -1;

    if (!ret){
        printf("请求主码流失败! 错误码为: %d\n", ARNET_GetLastError());
        return -1;
    }

    if(!logout()) {
        return -1;
    }

    if(!release()) {
        return -1;
    }

    printf("%s ret:%d", __FUNCTION__, ret);
    emit stopped();
    return 1;
}

void ArnetWrapper::resume() {
    play();
    isPlay = true;
    emit started();
}
void ArnetWrapper::pause() {
    stop();
    isPlay = false;
    emit paused();
}
void ArnetWrapper::toggle(){
    if(isPlay) {
       pause();
    } else {
       resume();
    }
}
bool ArnetWrapper::isWorking(){
    return isPlay;
}
bool ArnetWrapper::isPlaying(){
    return isPlay;
}

