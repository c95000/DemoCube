#ifndef MP4ENCODER_H
#define MP4ENCODER_H

#include <QObject>
extern "C"
{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
    #include "libavdevice/avdevice.h"
    #include "libavutil/opt.h"
}

class Mp4Encoder : public QObject
{
    Q_OBJECT
public:
    explicit Mp4Encoder(QObject *parent = nullptr);
    virtual ~Mp4Encoder();

signals:

public:
    int start(int width, int height, const char* output_file);
    int flush_encoder(AVFormatContext *fmt_ctx,unsigned int stream_index);
    int encode(const char* data, const int size);

    int yuv2h264_start(int width, int height);
    int yuv2h264_stop();
    int yuv2h264_encode(uint8_t* data, const int size, int64_t msec);

//    int h2642mp4();
    static int h2642mp4(const char *in_filename_v, const char *out_filename);
private:

    AVFormatContext* pFormatCtx;
    AVOutputFormat* fmt;
    AVStream* video_st;
    AVCodecContext* pCodecCtx;
    AVCodec* pCodec;
    AVPacket pkt;
    uint8_t* picture_buf;
    AVFrame* pFrame;
    QString outputFileName;
};

#endif // MP4ENCODER_H
