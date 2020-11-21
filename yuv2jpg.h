#ifndef YUV2JPG_H
#define YUV2JPG_H

#include <QObject>
extern "C"
{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
    #include "libavdevice/avdevice.h"
    #include "libavutil/opt.h"
    #include "libavutil/imgutils.h"
}

class YUV2JPG : public QObject
{
    Q_OBJECT
public:
    explicit YUV2JPG(QObject *parent = nullptr);
    ~YUV2JPG();

private:
    void init();
    void release();

signals:

public:
    void archive(const char* data, int width, int height, int align);

private:
    //为每帧图像分配内存
//    AVFrame *m_yuvFrame;
//    AVFrame *m_rgbFrame;
//    uint8_t *m_yuvBuffer;
//    uint8_t *m_rgbBuffer;
//    //特别注意sws_getContext内存泄露问题，
//    //注意sws_getContext只能调用一次，在初始化时候调用即可，另外调用完后，在析构函数中使用sws_freeContext，将它的内存释放。
//    //设置图像转换上下文
//    SwsContext *m_sws_context;

//    int width;
//    int height;
//    int align;
};

#endif // YUV2JPG_H
