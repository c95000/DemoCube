#ifndef FFDECODER_H
#define FFDECODER_H

#include <QThread>
#include "common.h"

extern "C"
{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
    #include "libavdevice/avdevice.h"
    #include "libavutil/opt.h"
    #include "libavutil/imgutils.h"
}

enum FFDECODER_STATE {
    FFDECODER_IDLE = 0,
    FFDECODER_PREPARING,
    FFDECODER_PLAYING,
    FFDECODER_PAUSED,
    FFDECODER_STOPPED,
    FFDECODER_ERROR,
};

typedef void (*ffdecoder_video_format_cb)(void *opaque, int* width, int *height, int* lineSize);
typedef void (*ffdecoder_data_available_cb)(void *opaque, const QByteArray& ba);

class FFDecoder : public QThread
{
    Q_OBJECT
public:
    explicit FFDecoder(QObject *parent = nullptr);
    virtual ~FFDecoder();

signals:
    void prepared();
    void played();
    void stopped();
    void paused();

public:
    void setSource(const QString& inputSrc, ffdecoder_video_format_cb video_format_cb = nullptr, ffdecoder_data_available_cb data_available_cb = nullptr, void* opaque = nullptr);
    void play();
    void stop();
    void pause();
    void resume();


protected:
    void run() override;

private:
    FFDECODER_STATE m_state;

    QString inputSource; // media source

    AVFormatContext*    p_fmt_ctx = NULL;
    AVCodecContext*     p_codec_ctx = NULL;
    AVCodecParameters*  p_codec_par = NULL;
    AVCodec*            p_codec = NULL;
    AVFrame*            p_frm_raw = NULL;        // 帧，由包解码得到原始帧
    AVFrame*            p_frm_yuv = NULL;        // 帧，由原始帧色彩转换得到
    AVPacket*           p_packet = NULL;         // 包，从流中读出的一段数据
    struct SwsContext*  sws_ctx = NULL;
    int                 buf_size;
    uint8_t*            buffer = NULL;
    int                 i;
    int                 v_idx;
    int                 ret;
    int                 align = 16;

    ffdecoder_video_format_cb video_format_cb;
    ffdecoder_data_available_cb data_available_cb;
    void* opaque;
};

#endif // FFDECODER_H
