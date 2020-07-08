#include "vlcwrapper.h"
#include "Util.h"
#include<iostream>

using namespace std;

VlcWrapper::VlcWrapper() : m_videobuf(NULL), vlcRenderCb(NULL)
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

void VlcWrapper::start(std::string source) {
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

    if(source.substr(0, 4) == "rtsp") {
        const char * rtsp = source.c_str();
        m_pvlcMedia = libvlc_media_new_location(m_vlcInstance, rtsp);

    } else {
        const char * local = source.c_str();
        m_pvlcMedia = libvlc_media_new_path(m_vlcInstance, local);
    }

    libvlc_media_player_set_media(m_vlcMediaPlayer, m_pvlcMedia);
    libvlc_video_set_callbacks(m_vlcMediaPlayer, preDecode_cb, handleStream_cb, render_cb, this);

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
}

void VlcWrapper::start(std::string source, VlcRenderCb* renderCb) {
    this->vlcRenderCb = renderCb;
    start(source);
}

void VlcWrapper::stop() {
    libvlc_media_player_stop(m_vlcMediaPlayer);
}

void VlcWrapper::pause() {
    libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
    if (state == libvlc_Playing)
    {
        libvlc_media_player_pause(m_vlcMediaPlayer);
        return;
    }
}

void VlcWrapper::resume() {
    libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
    if (state == libvlc_Paused)
    {
        libvlc_media_player_play(m_vlcMediaPlayer);
        return;
    }
}

void * VlcWrapper::preDecode_cb(void *opaque, void **planes) {
    VlcWrapper* obj = (VlcWrapper*)opaque;
    *planes = obj->m_videobuf;
    return obj->m_videobuf;
}

void VlcWrapper::handleStream_cb(void *opaque, void *picture, void *const *planes) {
    Q_UNUSED(opaque);
    Q_UNUSED(picture);
    Q_UNUSED(planes);
}

void VlcWrapper::render_cb(void *opaque, void *picture) {
    VlcWrapper* obj = (VlcWrapper*)opaque;
    QImage qimg((uchar*)picture, obj->m_frameWidth, obj->m_frameHeight, QImage::Format_ARGB32);
    //obj->ui->renderWidget->setPixmap(qimg);
    if(NULL != obj->vlcRenderCb) {
        obj->vlcRenderCb->onRender(qimg);
    }
    cout<<"save full screen failed"<<endl;
}
