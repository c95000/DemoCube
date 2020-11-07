#include "vlcwrapper.h"
#include "Util.h"
#include <iostream>
#include <QDateTime>
#include <QMutex>
#include <QDir>
#include "common.h"

using namespace std;

VlcWrapper::VlcWrapper() :
    m_videobuf(NULL), vlcRenderCb(NULL),
    isRtsp(false), rtspUrl(QString())
{
    char const* vlc_args[] =
    {
        "-I",
        "dummy",
        "--ignore-config",
    };

    m_vlcInstance = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
    m_vlcMediaPlayer = libvlc_media_player_new (m_vlcInstance);
}

VlcWrapper::~VlcWrapper() {
    libvlc_media_release(m_pvlcMedia);
    libvlc_media_player_stop(m_vlcMediaPlayer);
    libvlc_media_player_release(m_vlcMediaPlayer);
    libvlc_release(m_vlcInstance);
    SAFE_DELETE_ARRAY(m_videobuf);
}

void VlcWrapper::start(const QString& source) {
    libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
    if (state != libvlc_Stopped && state != libvlc_NothingSpecial)
    {
        libvlc_media_release(m_pvlcMedia);
        libvlc_media_player_stop(m_vlcMediaPlayer);
        while (state != libvlc_Stopped && state != libvlc_NothingSpecial)
        {
            state = libvlc_media_player_get_state(m_vlcMediaPlayer);
            MSleep(100);
        }
    }
    SAFE_DELETE_ARRAY(m_videobuf);

    if(source.left(4) == QString::fromLocal8Bit("rtsp")) {
        isRtsp = true;
        rtspUrl = source;
        const char * rtsp = source.toStdString().c_str();
        m_pvlcMedia = libvlc_media_new_location(m_vlcInstance, rtsp);

    } else {
        isRtsp = false;
        const char * local = source.toStdString().c_str();
        printf("wrapper local: %s", local);
        m_pvlcMedia = libvlc_media_new_path(m_vlcInstance, local);
    }

    libvlc_media_player_set_media(m_vlcMediaPlayer, m_pvlcMedia);
    libvlc_video_set_callbacks(m_vlcMediaPlayer, preDecode_cb, handleStream_cb, render_cb, this);
//    libvlc_video_set_format_callbacks(m_vlcMediaPlayer, video_format_cb, video_cleanup_cb);
    state = libvlc_media_player_get_state(m_vlcMediaPlayer);
    if (state == libvlc_Playing)
    {
        return;
    }

    libvlc_media_player_play(m_vlcMediaPlayer);
    while (state == libvlc_NothingSpecial || state == libvlc_Opening)
    {
        state = libvlc_media_player_get_state(m_vlcMediaPlayer);
        MSleep(100);
    }

    if (state == libvlc_Error)
    {
        return;
    }

    libvlc_media_track_t **tracks = NULL;
    bool bFindResolution = false;

    while (!bFindResolution)
    {
        unsigned tracksCount = libvlc_media_tracks_get(m_pvlcMedia, &tracks);

        if (tracks != NULL)
        {
            for (unsigned i = 0; i < tracksCount; i++)
            {
                if (tracks[i]->i_type == libvlc_track_video
                    && tracks[i]->video->i_height != 0
                    && tracks[i]->video->i_width != 0)
                {
                    m_frameWidth = tracks[i]->video->i_width;
                    m_frameHeight = tracks[i]->video->i_height;
                    bFindResolution = true;
                    break;
                }
            }
        }

        libvlc_media_tracks_release(tracks, tracksCount);
        MSleep(100);
    }

    // [workaround]: I don't know how to change format (libvlc_video_set_format) after playing...
    // reconnect the stream
    libvlc_media_player_stop(m_vlcMediaPlayer);

    libvlc_video_set_format(m_vlcMediaPlayer, "RV32", m_frameWidth, m_frameHeight, m_frameWidth << 2);

    m_videobuf = new char[(m_frameWidth * m_frameHeight) << 2];
    libvlc_media_player_play(m_vlcMediaPlayer);

    emit started();
}

void VlcWrapper::start(const QString& source, VideoRenderCallback* renderCb) {
    this->vlcRenderCb = renderCb;
    start(source);
}

void VlcWrapper::stop() {
    libvlc_media_player_stop(m_vlcMediaPlayer);
    emit stopped();
}

void VlcWrapper::pause() {
    libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
    if (state == libvlc_Playing)
    {
        libvlc_media_player_pause(m_vlcMediaPlayer);
        emit paused();
    }
}

void VlcWrapper::toggle() {
    libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
    if(!isRtsp)
    {
        if (state == libvlc_Playing)
        {
            libvlc_media_player_pause(m_vlcMediaPlayer);
            emit paused();
        }
        else if(state == libvlc_Paused)
        {
            libvlc_media_player_play(m_vlcMediaPlayer);
            emit started();
        }
    }
    else
    {
        if (state == libvlc_Playing)
        {
            libvlc_media_player_pause(m_vlcMediaPlayer);
            emit paused();
        }
        else if(state == libvlc_Paused)
        {
            start(rtspUrl);
            emit started();
        }
    }
}

bool VlcWrapper::isWorking() {
    libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
    printf("state: %d", state);
    if (state == libvlc_Opening || state == libvlc_Buffering || state == libvlc_Playing || state == libvlc_Paused)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool VlcWrapper::isPlaying() {
    int isPlaying = libvlc_media_player_is_playing(m_vlcMediaPlayer);
    printf("isPlaying: %d", isPlaying);
    if(1 == isPlaying)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void VlcWrapper::resume() {
    libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
    if (state == libvlc_Paused)
    {
        libvlc_media_player_play(m_vlcMediaPlayer);
        emit started();
    }
}

static QMutex g_mutex;
static int g_count = 0;

void * VlcWrapper::preDecode_cb(void *opaque, void **planes) {
    printf("chengjl %s opaque:%p", __FUNCTION__, opaque);
    VlcWrapper* obj = (VlcWrapper*)opaque;
    *planes = obj->m_videobuf;
    return obj->m_videobuf;
}


//QImage image((unsigned char*)out_buffer,640,480,QImage::Format_ARGB32);
//    std::ostringstream oss;
//    oss << "d:/img"
//        << frameNum
//        << ".jpg";
//    frameNum++;
//    image.save(oss.str().c_str());
//    g_mutex.unlock();

void VlcWrapper::handleStream_cb(void *opaque, void *picture, void *const *planes) {
    Q_UNUSED(opaque);
    Q_UNUSED(picture);
    Q_UNUSED(planes);
//    printf("chengjl %s picture:%p planes:%p", __FUNCTION__, picture, planes);
//    VlcWrapper* obj = (VlcWrapper*)opaque;
//    QImage qimg((uchar*)planes, obj->m_frameWidth, obj->m_frameHeight, QImage::Format_ARGB32);

//    VlcWrapper* obj = (VlcWrapper*)opaque;
//    if(NULL != obj->vlcRenderCb) {
//        obj->vlcRenderCb->renderYUV((uchar*)picture, 1280, 738, 0);
//    }
}

void VlcWrapper::render_cb(void *opaque, void *picture) {
//    printf("chengjl %s opaque:%p picture:%p", __FUNCTION__, opaque, picture);
    VlcWrapper* obj = (VlcWrapper*)opaque;
    if(NULL != picture) {
        QImage qimg((uchar*)picture, obj->m_frameWidth, obj->m_frameHeight, QImage::Format_ARGB32);
        if(NULL != obj->vlcRenderCb) {
            obj->vlcRenderCb->onRender(qimg);
//            saveImage(qimg);
        }
    }
}

unsigned VlcWrapper::video_format_cb(void **opaque, char *chroma,
                                   unsigned *width, unsigned *height,
                                   unsigned *pitches,
                                    unsigned *lines) {
    printf("chengjl %s opaque:%p(%p) chroma:%s w:%d h:%d", __FUNCTION__, *opaque, opaque, chroma, *width, *height);
    VlcWrapper* obj = (VlcWrapper*)*opaque;
    SAFE_DELETE_ARRAY(obj->m_videobuf);
    obj->m_videobuf = new char[(*width * *height) << 2];
    printf("chengjl %s videobuf:%p", __FUNCTION__, obj->m_videobuf);

//    libvlc_video_set_format(obj->m_vlcMediaPlayer, "RV32", *width, *height, (*width) << 2);

    return 1;
}

void VlcWrapper::video_cleanup_cb(void *opaque) {
    printf("chengjl %s opaque:%p", __FUNCTION__, opaque);
    VlcWrapper* obj = (VlcWrapper*)opaque;
    SAFE_DELETE_ARRAY(obj->m_videobuf);
}
