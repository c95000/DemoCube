#include "jyplayer.h"


#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#define printf qDebug

JyPlayer::JyPlayer(const QString& inputsource, QObject *parent) : QThread(parent)
  ,source(inputsource)
  ,state(0)
  ,glVideoWidget(nullptr)
{

}

static void printError(int ret) {
    char msg[512];
    av_make_error_string(msg, 512, ret);
    printf("Error(%d)(%s).\n", ret, msg);
}

static void writeFile(const QString& filename, const char* data, int size) {
    QFile f(filename);
    f.open(QIODevice::WriteOnly | QIODevice::Append);
    f.write(data, size);
    f.close();
}

void JyPlayer::run() {
    printf("run -- begin");

    int count = 0;

    int ret = 0;
    av_register_all();
    ret = avformat_network_init();

    AVFormatContext *pFormatCtx = avformat_alloc_context();
    printf("%s() pFormatCtx:%p", __FUNCTION__, pFormatCtx);
//    ret = avformat_open_input(&pFormatCtx, "D:/vs/yuvrender/test.yuv", NULL, NULL);
//    ret = avformat_open_input(&pFormatCtx, "D:\\vs\\output.mp4", NULL, NULL);
    ret = avformat_open_input(&pFormatCtx, "rtsp://192.168.1.225", NULL, NULL);
    printf("%s() ret:%d", __FUNCTION__, ret);
    if(ret < 0) {
        printError(ret);
        return;
    }

    ret = avformat_find_stream_info(pFormatCtx,NULL);
    if(ret < 0) {
        printError(ret);
        return;
    }

    AVCodecContext *pCodecCtx, *pACodecCtx;
    AVCodec *pCodec, *pACodec;

    for(int i = 0; i < pFormatCtx->nb_streams; i++) {
        printf("stream[%d] codec_type:%d", i, pFormatCtx->streams[i]->codec->codec_type);
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
        {
            pCodecCtx = pFormatCtx->streams[i]->codec;
            printf("stream[%d] codec_id:%d", i, pCodecCtx->codec_id);
            pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
            if(NULL == pCodec) {
                printf("stream[%d] pCodec:%s", i, pCodec->name);
                printf("video Codec not found.\n");
                return;
            }
        }
        else
        {
            pACodecCtx = pFormatCtx->streams[i]->codec;
            printf("stream[%d] codec_id:%d", i, pACodecCtx->codec_id);
            pACodec = avcodec_find_decoder(pACodecCtx->codec_id);
            if(NULL == pACodec) {
                printf("stream[%d] pCodec:%s", i, pACodec->name);
                printf("audio Codec not found.\n");
            }
        }
    }

    ret = avcodec_open2(pCodecCtx, pCodec, NULL);
    if(ret < 0)
    {
        printError(ret);
        return;
    }

    //输出视频信息
    printf("video format: %s",pFormatCtx->iformat->name);
    printf("video length: %d", (pFormatCtx->duration)/1000000);
    printf("video size: %d,%d",pCodecCtx->width,pCodecCtx->height);
    printf("codec name: %s",pCodec->name);

    if(nullptr != glVideoWidget) {
        glVideoWidget->setYUV420pParameters(pCodecCtx->width,pCodecCtx->height);
    }

    FILE* h264File = fopen(h264FileName.toStdString().c_str(), "wba");


    AVFrame *pFrame    = av_frame_alloc();
    AVFrame *pFrameYUV = av_frame_alloc();

    AVPacket *pAVpackage = av_packet_alloc();
    do {
        ret = av_read_frame(pFormatCtx, pAVpackage);
        if(ret < 0) {
            printError(ret);
            break;
        }

        printf("pAVpackage pts:%ld dts:%ld duration:%ld codec_type:%d",
               pAVpackage->pts, pAVpackage->dts, pAVpackage->duration,
               pFormatCtx->streams[pAVpackage->stream_index]->codec->codec_type);

        if(NULL != h264File) {
            fwrite(pAVpackage->buf->data, pAVpackage->buf->size, 1, h264File);
        }
//        printf("buffer:%p size:%d data:%p (%d %p)",
//               pAVpackage->buf->buffer,
//               pAVpackage->buf->size,
//               pAVpackage->buf->data,
//               pAVpackage->size,
//               pAVpackage->data);

        int got_picture_ptr = 0;

        if(pFormatCtx->streams[pAVpackage->stream_index]->codec->codec_type==AVMediaType::AVMEDIA_TYPE_VIDEO) {
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture_ptr, pAVpackage);
            if(ret < 0) {
                printError(ret);
                break;
            }

            printf("got_picture_ptr:%d format:%d  %d x %d picType:%d", got_picture_ptr, pFrame->format, pFrame->width, pFrame->height, pFrame->pict_type);
            if(got_picture_ptr) {
                if( pFrame->format == AVPixelFormat::AV_PIX_FMT_YUVJ420P) {
                    char* buf = new char[pCodecCtx->height * pCodecCtx->width * 3 / 2];
                    memset(buf, 0, pCodecCtx->height * pCodecCtx->width * 3 / 2);
                    int height = pCodecCtx->height;
                    int width = pCodecCtx->width;

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

                    if(nullptr != glVideoWidget) {
                        QByteArray ba = QByteArray(buf, pCodecCtx->height * pCodecCtx->width * 3 / 2);
                        printf("buf:%p ba:%p", buf, ba.data());
                        glVideoWidget->setFrameData(ba);
                    }
//                    if(count ++ % 100 == 0) {
//                        QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
//                        QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".yuv";
//                        writeFile(fileName, buf, pCodecCtx->height * pCodecCtx->width * 3 / 2);
//                    }

                    delete [] buf;
                }
            }
        }
    } while(state > 0);
    av_packet_free(&pAVpackage);


    while(state > 0) {
        //        printf("readSize:%d", readSize);
//        QString date = QDateTime::currentDateTime().toString("欢迎使用软件, 现在时刻：yyyy-MM-dd hh:mm:ss.zzz");
        QString time = QDateTime::currentDateTime().toString();
        printf("current Time: %s", time.toStdString().c_str());
        thread()->sleep(1);
    }


    printf("run -- exit");
}

int JyPlayer::startPlay(GLVideoWidget* glVideoWidget) {
    this->glVideoWidget = glVideoWidget;

    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    h264FileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".h264";

    return startPlay();
}

int JyPlayer::startPlay() {
    state = 1;
    start();
    return 0;
}

int JyPlayer::stopPlay() {
    state = 0;
    printf("stopPlay -- ");
    quit();
    printf("stopPlay -- quit");
    wait();
    printf("stopPlay -- wait");

    return 0;
}

