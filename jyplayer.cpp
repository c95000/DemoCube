#include "jyplayer.h"


#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include "Configure.h"
#include "mp4encoder.h"
#include <QDebug>
#define printf qDebug

JyPlayer::JyPlayer(const QString& inputsource, QObject *parent) : QThread(parent)
  ,source(inputsource)
  ,state(IDLE)
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
    AVDictionary *options = NULL;

    av_dict_set(&options, "rtsp_transport" , "tcp", 0);

    AVFormatContext *pFormatCtx = avformat_alloc_context();
    printf("%s() pFormatCtx:%p", __FUNCTION__, pFormatCtx);
//    ret = avformat_open_input(&pFormatCtx, "D:/vs/yuvrender/test.yuv", NULL, NULL);
//    ret = avformat_open_input(&pFormatCtx, "D:\\vs\\output.mp4", NULL, NULL);
//    ret = avformat_open_input(&pFormatCtx, "rtsp://192.168.1.225", NULL, &options);
    ret = avformat_open_input(&pFormatCtx, source.toStdString().c_str(), NULL, &options);
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

//    FILE* h264File = fopen(h264FileName.toStdString().c_str(), "wba");


    AVFrame *pFrame    = av_frame_alloc();
    AVPacket *pAVpackage = av_packet_alloc();
    do {
        ret = av_read_frame(pFormatCtx, pAVpackage);
        if(ret < 0) {
            printError(ret);
            break;
        }

//        printf("pAVpackage pts:%ld dts:%ld duration:%ld codec_type:%d",
//               pAVpackage->pts, pAVpackage->dts, pAVpackage->duration,
//               pFormatCtx->streams[pAVpackage->stream_index]->codec->codec_type);

//        if(NULL != h264File) {
//            fwrite(pAVpackage->buf->data, pAVpackage->buf->size, 1, h264File);
//        }
//        printf("buffer:%p size:%d data:%p (%d %p)",
//               pAVpackage->buf->buffer,
//               pAVpackage->buf->size,
//               pAVpackage->buf->data,
//               pAVpackage->size,
//               pAVpackage->data);

//        if(isRecording && NULL != h264File) {
//            printf("buffer:%p size:%d data:%p (%d %p)",
//                   pAVpackage->buf->buffer,
//                   pAVpackage->buf->size,
//                   pAVpackage->buf->data,
//                   pAVpackage->size,
//                   pAVpackage->data);
//            fwrite(pAVpackage->buf->data, pAVpackage->buf->size, 1, h264File);
//        }

        int got_picture_ptr = 0;

        if(pFormatCtx->streams[pAVpackage->stream_index]->codec->codec_type==AVMediaType::AVMEDIA_TYPE_VIDEO) {
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture_ptr, pAVpackage);
            if(ret < 0) {
                printError(ret);
                break;
            }


            if(isRecording) {
                if(!isGotIFrame && pFrame->pict_type == AVPictureType::AV_PICTURE_TYPE_I) {
                    isGotIFrame = true;
                    emit recordStarted();
                }
                if(isGotIFrame) {
                    if(pAVpackage->buf->size == 0 || pAVpackage->buf->data == NULL) {
                        printf("buffer:%p size:%d data:%p (%d %p)",
                               pAVpackage->buf->buffer,
                               pAVpackage->buf->size,
                               pAVpackage->buf->data,
                               pAVpackage->size,
                               pAVpackage->data);
                    }
//                    fwrite(pAVpackage->buf->data, pAVpackage->buf->size, 1, h264File);
                    qh264File.write((const char *)(pAVpackage->buf->data), pAVpackage->buf->size);
                }
            }

//            printf("got_picture_ptr:%d format:%d  %d x %d picType:%d", got_picture_ptr, pFrame->format, pFrame->width, pFrame->height, pFrame->pict_type);
            if(got_picture_ptr) {
                if(state == PREPARING) {
                    setState(PLAYING);
                }
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
//                        printf("buf:%p ba:%p", buf, ba.data());
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
    } while(state == PREPARING || state == PLAYING);

    av_packet_free(&pAVpackage);
    av_frame_free(&pFrame);


//    while(state > 0) {
//        QString time = QDateTime::currentDateTime().toString();
//        printf("current Time: %s", time.toStdString().c_str());
//        thread()->sleep(1);
//    }

    printf("run -- exit");
}

int JyPlayer::startPlay(const QString& inputsource, GLVideoWidget* glVideoWidget) {
    this->source = inputsource;
    this->glVideoWidget = glVideoWidget;

    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    h264FileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".h264";

    return startPlay();
}

int JyPlayer::startPlay() {
    setState(enJYPLAYER_STATE::PREPARING);
    start();
    return 0;
}

int JyPlayer::stopPlay() {
    setState(enJYPLAYER_STATE::STOPPED);
    printf("stopPlay -- ");
    quit();
    printf("stopPlay -- quit");
    wait();
    printf("stopPlay -- wait");

    return 0;
}

int JyPlayer::pausePlay() {
    setState(enJYPLAYER_STATE::PAUSED);
}

int JyPlayer::resumePlay() {

}

int JyPlayer::togglePlay() {
    if(state == PREPARING || state == PLAYING)
    {
        stopPlay();
    }
    else
    {
        startPlay();
    }
}

bool JyPlayer::isWorking() {
    if(state != IDLE) {
        return true;
    } else {
        return false;
    }
}

int JyPlayer::startRecord() {
    if(state == PLAYING && !isRecording) {
        recordedFileName = Configure::getInstance()->getVideopath() + QDir::separator() +
                    QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
//        if(NULL == h264File) {
//            h264File = fopen(recordedFileName.toStdString().c_str(), "wba");
//        }
        qh264File.setFileName(recordedFileName + ".h264");
        qh264File.open(QIODevice::ReadWrite);
        isGotIFrame = false;
        isRecording = true;
    }
    return 0;
}

int JyPlayer::stopRecord() {
    if(state == PLAYING && isRecording) {
        isRecording = false;
        qh264File.flush();
        qh264File.close();

        Mp4Encoder::h2642mp4((recordedFileName + ".h264").toStdString().c_str(),
                             ((recordedFileName + ".mp4")).toStdString().c_str());
        QFile::remove(recordedFileName + ".h264");
    }
    return 0;
}

void JyPlayer::setState(enJYPLAYER_STATE state){
    if(this->state == state) {
        return;
    }

    this->state = state;
    if(state == PLAYING) {
        emit started();
    } else if(state == STOPPED) {
        emit stopped();
    } else if(state == PAUSED) {
        emit paused();
    }
}

