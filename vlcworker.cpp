#include "vlcworker.h"
#include <QThread>
#include "common.h"
#include "Util.h"


void *preDecode_cb(void *opaque, void **planes) {
//    printf("chengjl %s opaque:%p", __FUNCTION__, opaque);
    VlcWorker* obj = (VlcWorker*)opaque;
    *planes = obj->m_videobuf;
    return obj->m_videobuf;
}

void handleStream_cb(void *opaque, void *picture, void *const *planes) {
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

void render_cb(void *opaque, void *picture) {
//    printf("chengjl %s opaque:%p picture:%p", __FUNCTION__, opaque, picture);
    VlcWorker* obj = (VlcWorker*)opaque;
    if(NULL != picture) {
        printf("picture: %p", picture);
//        QImage qimg((uchar*)picture, obj->m_frameWidth, obj->m_frameHeight, QImage::Format_ARGB32);
//        if(NULL != obj->vlcRenderCb) {
//            obj->vlcRenderCb->onRender(qimg);
//        }
    }
}



VlcWorker::VlcWorker(const QString& inputsrc, QObject *parent) : inputSource(inputsrc)
{
}

VlcWorker::~VlcWorker() {
//    deinitVlc();
}


void VlcWorker::initVlc() {
    printf("VlcWorker::initVlc:%p", QThread::currentThreadId());
    char const* vlc_args[] =
    {
        "-I",
        "dummy",
        "--ignore-config",
    };

    m_vlcInstance = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
    m_vlcMediaPlayer = libvlc_media_player_new (m_vlcInstance);
}

void VlcWorker::deinitVlc() {
    printf("VlcWorker::deinitVlc :%p", QThread::currentThreadId());
    libvlc_media_release(m_pvlcMedia);
    libvlc_media_player_stop(m_vlcMediaPlayer);
    libvlc_media_player_release(m_vlcMediaPlayer);
    libvlc_release(m_vlcInstance);
}

void VlcWorker::onPlay() {
    printf("%s() : %p", __FUNCTION__, QThread::currentThreadId());

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

    std::string local = inputSource.toStdString();
    m_pvlcMedia = libvlc_media_new_path(m_vlcInstance, local.c_str());

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
//                    m_frameWidth = tracks[i]->video->i_width;
//                    m_frameHeight = tracks[i]->video->i_height;
                    printf("resolution: %d x %d", tracks[i]->video->i_width, tracks[i]->video->i_height);
                    bFindResolution = true;
                    break;
                }
            }
        }

        libvlc_media_tracks_release(tracks, tracksCount);
        MSleep(100);
    }

//     [workaround]: I don't know how to change format (libvlc_video_set_format) after playing...
//     reconnect the stream
//    libvlc_media_player_stop(m_vlcMediaPlayer);

//    libvlc_video_set_format(m_vlcMediaPlayer, "RV32", m_frameWidth, m_frameHeight, m_frameWidth << 2);

//    m_videobuf = new char[(m_frameWidth * m_frameHeight) << 2];
//    libvlc_media_player_play(m_vlcMediaPlayer);
}
void VlcWorker::onStop() {
    printf("%s() : %p", __FUNCTION__, QThread::currentThreadId());
    QThread::sleep(5);
    printf("%s() : %p", __FUNCTION__, QThread::currentThreadId());
}
void VlcWorker::onPause() {
    printf("%s() : %p", __FUNCTION__, QThread::currentThreadId());
    QThread *th = new QThread();
    moveToThread(th);
    printf("%s() : %p", __FUNCTION__, QThread::currentThreadId());
}
void VlcWorker::onResume() {
    printf("%s() : %p", __FUNCTION__, QThread::currentThreadId());
}
void VlcWorker::onExit() {
    printf("%s() : %p", __FUNCTION__, QThread::currentThreadId());
}
