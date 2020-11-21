#include "yuv2jpg.h"
#include <QStandardPaths>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include "common.h"
#include <QImage>

static void writeFile(const char* data, int size) {
    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".out";

    QFile f(fileName);
    f.open(QIODevice::WriteOnly | QIODevice::Append);
    f.write(data, size);
    f.close();
}

static void savePicture(const QImage& img) {
    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".png";
    img.save(fileName);
}

YUV2JPG::YUV2JPG(QObject *parent) : QObject(parent)
{
    init();
}

YUV2JPG::~YUV2JPG() {
    release();
}

void YUV2JPG::init() {
    printf("%s is called", __FUNCTION__);
}

void YUV2JPG::release() {
    printf("%s is called", __FUNCTION__);
}

void YUV2JPG::archive(const char* data, int width, int height, int align) {

    //为每帧图像分配内存
    AVFrame *m_yuvFrame = av_frame_alloc();
    AVFrame *m_rgbFrame = av_frame_alloc();

    int yuv_size = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, width, height, align);
    uint8_t *m_yuvBuffer = (uint8_t *) av_malloc(yuv_size * sizeof(uint8_t));

    // width和heigt为传入的分辨率的大小，分辨率有变化时可以以最大标准申请
    int rgb_size = av_image_get_buffer_size(AV_PIX_FMT_BGRA, width, height, align);
    uint8_t *m_rgbBuffer = (uint8_t *) av_malloc(rgb_size * sizeof(uint8_t));

    //特别注意sws_getContext内存泄露问题，
        //注意sws_getContext只能调用一次，在初始化时候调用即可，另外调用完后，在析构函数中使用sws_freeContext，将它的内存释放。
        //设置图像转换上下文
    SwsContext *m_sws_context = sws_getContext(width, height, AV_PIX_FMT_YUV420P,
                                   width, height, AV_PIX_FMT_BGRA, SWS_BICUBIC, NULL, NULL, NULL);


    // 使用给定参数设定p_frm_yuv->data和p_frm_yuv->linesize
    int ret = av_image_fill_arrays(m_yuvFrame->data,           // dst data[]
                        m_yuvFrame->linesize,       // dst linesize[]
                        (const uint8_t *)data,                    // src buffer
                        AV_PIX_FMT_YUV420P,        // pixel format
                        width,        // width
                        height,       // height
                        align                          // align
                       );

    // 使用给定参数设定p_frm_yuv->data和p_frm_yuv->linesize
    ret = av_image_fill_arrays(m_rgbFrame->data,           // dst data[]
                        m_rgbFrame->linesize,       // dst linesize[]
                        m_rgbBuffer,                    // src buffer
                        AV_PIX_FMT_BGRA,        // pixel format
                        width,        // width
                        height,       // height
                        align                          // align
                       );

    //转换图像格式，将解压出来的YUV420P的图像转换为RGB的图像
    ret =sws_scale(m_sws_context,
            (uint8_t const * const *) m_yuvFrame->data,
            m_yuvFrame->linesize, 0, height, m_rgbFrame->data,
            m_rgbFrame->linesize);


    QImage img(m_rgbFrame->data[0], width, height, QImage::Format_ARGB32);
    savePicture(img);

    av_frame_free(&m_yuvFrame);
    av_frame_free(&m_rgbFrame);
    av_free(m_rgbBuffer);
    av_free(m_yuvBuffer);
    sws_freeContext(m_sws_context);
}
