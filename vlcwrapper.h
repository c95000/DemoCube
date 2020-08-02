#ifndef VLCWRAPPER_H
#define VLCWRAPPER_H

#include <string>
#include "vlc/vlc.h"
#include <QObject>
#include <QImage>

class VlcRenderCb {
public:
    virtual void onRender(const QImage &pixmap) = 0;
};

class VlcWrapper : public QObject
{
    Q_OBJECT
public:
    VlcWrapper();
    ~VlcWrapper();

signals:
    void started();
    void paused();
    void stopped();
    void error(QString& err);

public:
    void start(const QString& source, VlcRenderCb* renderCb);
    void stop();
    void resume();
    void pause();
    void toggle();
    bool isWorking();
    bool isPlaying();

private:
    void start(const QString& source);
    static void* preDecode_cb(void *opaque, void **planes);
    static void handleStream_cb(void *opaque, void *picture, void *const *planes);
    static void render_cb(void *opaque, void *picture);

private:
    libvlc_instance_t* m_vlcInstance;
    libvlc_media_player_t* m_vlcMediaPlayer;
    libvlc_media_t* m_pvlcMedia;

    char * m_videobuf;
    int m_frameWidth;
    int m_frameHeight;

    bool isRtsp;
    QString rtspUrl;

    VlcRenderCb* vlcRenderCb;
};

#endif // VLCWRAPPER_H
