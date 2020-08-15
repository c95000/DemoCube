#include "ArnetWrapper.h"
#include "XPlay.h"

ArnetWrapper::ArnetWrapper(const QString& ip):ip(ip)
{
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
    printf("%s pBuf:%p nSize:%ld pUser：%p", __FUNCTION__, pBuf, nSize, pUser);
    printf("%s pFrameInfo: %ld %ld %ld %ld %ld", __FUNCTION__,
           pFrameInfo->nType, pFrameInfo->nStamp,
           pFrameInfo->nWidth, pFrameInfo->nHeight, pFrameInfo->nFrameRate);
}

int ArnetWrapper::init() {
    m_lLoginHandle = -1;
    m_lRealHandle = -1;
    m_lPlayHandle = -1;

    BOOL ret = ARNET_Init(NULL);
    return ret;
}

int ArnetWrapper::release() {
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

int ArnetWrapper::login() {

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
        printf("error :%d", error);
        return error;
    }
    printf("m_lLoginHandle :%ld", m_lLoginHandle);

    return (int)m_lLoginHandle;
}

int ArnetWrapper::logout() {
    BOOL ret = ARNET_LogOut(m_lLoginHandle);
    printf("%s ret:%d", __FUNCTION__, ret);
    return ret;
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
    }
    return 1;
}

int ArnetWrapper::stop() {
    BOOL ret = ARNET_StopRealPlay(m_lRealHandle);
    if (!ret){
        printf("请求主码流失败! 错误码为: %d\n", ARNET_GetLastError());
        return -1;
    }
    printf("%s ret:%d", __FUNCTION__, ret);
    return 1;
}
