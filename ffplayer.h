#ifndef FFPLAYER_H
#define FFPLAYER_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QFile>
#include "ffdecoder.h"
#include "glvideowidget.h"

extern "C"
{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
    #include "libavdevice/avdevice.h"
    #include "libavutil/opt.h"
    #include "libavutil/imgutils.h"
}

class FFPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit FFPlayer(QWidget *parent = nullptr);
    explicit FFPlayer(const QString& inputSrc, QWidget *parent = nullptr);
    ~FFPlayer();
private:
    void init();

signals:
    void prepared();
    void played();
    void paused();
    void stopped();

public slots:
    void play(const QString& inputSrc);
    void play();
    void stop();
    void pause();
    void close();
    void takePicture();
    void comment();

public:
    const QPixmap snapshot();

public:
    GLVideoWidget* videoView;

private:
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

    FFDecoder*          ffDecoder;
};

#endif // FFPLAYER_H