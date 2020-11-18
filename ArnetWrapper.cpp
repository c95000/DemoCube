#include "ArnetWrapper.h"
#include "XPlay.h"
#include "Record_SDK.h"
#include <QtConcurrent/QtConcurrent>
#include <Configure.h>
#include <QFileDialog>

AVCodec *codec;
AVCodecContext *context;


ArnetWrapper::ArnetWrapper():isPlay(false)
  , isRecording(FALSE)
  , mp4Encoder(NULL)
{
    m_lLoginHandle = -1;
    m_lRealHandle = -1;
    m_lPlayHandle = -1;
    init();

    av_register_all();
    avformat_network_init();

    codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!codec) {
        return;
    }

    context = avcodec_alloc_context3(codec);
    if (avcodec_open2(context, codec, NULL) < 0) {
        return;
    }
}

ArnetWrapper::~ArnetWrapper()
{
    if(NULL != mp4Encoder) {
        delete mp4Encoder;
        mp4Encoder = NULL;
    }

    avcodec_free_context(&context);
}

static void printError(int ret) {
    char msg[512];
    av_make_error_string(msg, 512, ret);
    printf("Error(%d)(%s).\n", ret, msg);
}

int count = 0;
FILE* h264File = NULL;

static void writeFile(const QString& filename, const char* data, int size) {
    QFile f(filename);
    f.open(QIODevice::WriteOnly | QIODevice::Append);
    f.write(data, size);
    f.close();
}

void WINAPI RealDataCallBack(LONG lRealHandle, char *pBuffer, DWORD dwBufSize, ARNET_FRAME_INFO *pFrameInfo, void* pUser) {
//    printf("%s lRealHandle:%ld pBuffer:%p bufSize:%ld data:%p", __FUNCTION__,
//           lRealHandle, pBuffer, dwBufSize, pUser);

    printf("nFrameType:%d", pFrameInfo->nFrameType);
    ArnetWrapper *arnetWrapper=(ArnetWrapper*)pUser;

    UINT64 u64Time = 0;
    u64Time = (UINT64)pFrameInfo->secCapTime * 1000 + pFrameInfo->usecCapTime / 1000;

    if(arnetWrapper->isRecording) {

        if(NULL == arnetWrapper->h264File && pFrameInfo->nFrameType == 0) {
            arnetWrapper->h264File = fopen(arnetWrapper->recordedFileName.toStdString().c_str(), "wba");
        }
        if(NULL != arnetWrapper->h264File) {
            fwrite(pBuffer, dwBufSize, 1, arnetWrapper->h264File);
        }
    }



    AVPacket avpackage;
    av_init_packet(&avpackage);

    int ret = av_packet_from_data(&avpackage, ( uint8_t *)pBuffer, dwBufSize);
    if(0 != ret) {
        printf("error! \n");
    }

//    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
//    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".h264";
//    if(NULL == h264File) {
//        h264File = fopen(fileName.toStdString().c_str(), "wba");
//    }
//    AVPacket *pAVpackage = &avpackage;
//    if(NULL != h264File) {
//        fwrite(pAVpackage->buf->data, pAVpackage->buf->size, 1, h264File);
//    }

    AVFrame *pFrame = av_frame_alloc();
    int got_picture_ptr = 0;
    ret = avcodec_decode_video2(context, pFrame, &got_picture_ptr, &avpackage);
    if(ret < 0) {
        printError(ret);
        return;
    }

    printf("got_picture_ptr:%d format:%d  %d x %d picType:%d", got_picture_ptr, pFrame->format, pFrame->width, pFrame->height, pFrame->pict_type);
    if( pFrame->format == AVPixelFormat::AV_PIX_FMT_YUVJ420P) {
        char* buf = new char[pFrame->height * pFrame->width * 3 / 2];
        memset(buf, 0, pFrame->height * pFrame->width * 3 / 2);
        int height = pFrame->height;
        int width = pFrame->width;


        int a = 0, i;
        for (i = 0; i<height; i++)
        {
           memcpy(buf + a, pFrame->data[0] + i * pFrame->linesize[0], width);
           a += width;
        }
        for (i = 0; i<height / 2; i++)
        {
           memcpy(buf + a, pFrame->data[1] + i * pFrame->linesize[1], width / 2);
           a += width / 2;
        }
        for (i = 0; i<height / 2; i++)
        {
           memcpy(buf + a, pFrame->data[2] + i * pFrame->linesize[2], width / 2);
           a += width / 2;
        }

        if(nullptr != arnetWrapper->videoWidget) {
            arnetWrapper->videoWidget->setYUV420pParameters(width, height);
            QByteArray ba = QByteArray(buf, height * width * 3 / 2);
            printf("buf:%p ba:%p", buf, ba.data());
            arnetWrapper->videoWidget->setFrameData(ba);
        }

//        if(nullptr != glVideoWidget) {
//            QByteArray ba = QByteArray(buf, pCodecCtx->height * pCodecCtx->width * 3 / 2);
//            printf("buf:%p ba:%p", buf, ba.data());
//            glVideoWidget->setFrameData(ba);
//        }
        QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".yuv";

        if(pFrameInfo->nFrameType == 0) {
            writeFile(fileName, buf, pFrame->height * pFrame->width * 3 / 2);
        }

        delete [] buf;
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

int ArnetWrapper::start(const QString& ip, GLVideoWidget* videoWidget) {
    this->videoWidget = videoWidget;
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

//int ArnetWrapper::start(const QString& ip, VideoRenderCallback* renderCb) {
//    this->renderCallback = renderCb;
//    this->ip = ip;

//    if(ip.isNull() || ip.isEmpty()) {
//        return -1;
//    }

//    if(!login()) {
//        return -1;
//    }

//    int ret = play();
//    return ret;
//}

//int ArnetWrapper::playFile(const QString& fileName, VideoRenderCallback* renderCb) {

//}

int ArnetWrapper::play() {
//    m_lPlayHandle = X_OpenStream2(X_STREAM_REALTIME, X_Draw_Balanced, X_DECTYPE_IntelGpu);

    m_lRealHandle = ARNET_StartRealPlay(m_lLoginHandle, 0, MBT_VIDEOPS, RealDataCallBack, this);
    if (m_lRealHandle < 0)
    {
        printf("请求主码流失败! 错误码为: %d\n", ARNET_GetLastError());
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

void ArnetWrapper::zoomWide() {
    if(isPlaying()) {
        BOOL ret = ARNET_PtzCtrl(m_lLoginHandle, SP_ZOOM_WIDE, 0, 0);
        if (!ret){
            printf("zoomWide failed. errCode: %d\n", ARNET_GetLastError());
            return;
        }
        QtConcurrent::run(this, &ArnetWrapper::zoomStop);
    }
}

void ArnetWrapper::zoomTele() {
    if(isPlaying()) {
        BOOL ret = ARNET_PtzCtrl(m_lLoginHandle, SP_ZOOM_TELE, 0, 0);
        if (!ret){
            printf("zoomTele failed. errCode: %d\n", ARNET_GetLastError());
            return;
        }
        QtConcurrent::run(this, &ArnetWrapper::zoomStop);
    }
}

void ArnetWrapper::zoomStop() {
    QThread::msleep(250);
    BOOL ret = ARNET_PtzCtrl(m_lLoginHandle, SP_PTZ_STOP, 0, 0);
    if (!ret){
        printf("zoomTele failed. errCode: %d\n", ARNET_GetLastError());
        return;
    }
}

void ArnetWrapper::startRecord() {
    printf("startRecord");
//    if(NULL == mp4Encoder) {
//        mp4Encoder = new Mp4Encoder();
//    }
//    mp4Encoder->yuv2h264_start(m_frameWidth, m_frameHeight);

    recordedFileName = Configure::getInstance()->getVideopath() + QDir::separator() +
            QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".h264";
    isRecording = TRUE;
}

void ArnetWrapper::stopRecord() {
    printf("stopRecord");
    isRecording = FALSE;
//    mp4Encoder->yuv2h264_stop();
    printf("Line:%d %s()", __LINE__, __FUNCTION__);
//    mp4Encoder->h2642mp4();

    fflush(h264File);
    fclose(h264File);
    h264File = NULL;
}

