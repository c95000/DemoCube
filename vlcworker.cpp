#include "vlcworker.h"
#include <QThread>
#include "common.h"
#include "Util.h"
#include <QFile>

static void writeFile(const QString& filename, const char* data, int size) {
    QFile f(filename);
    f.open(QIODevice::WriteOnly | QIODevice::Append);
    f.write(data, size);
    f.close();
}

//                        QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
//                        QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".yuv";
//                        writeFile(fileName, buf, pCodecCtx->height * pCodecCtx->width * 3 / 2);
static QString m_filename;
static int m_videobuf_size = 0;
static int m_width;
static int m_height;
static char* m_videobuf = NULL;
static int count = 0;

static void *video_lock_cb(void *opaque, void **planes) {
    printf("%s opaque:%p\n", __FUNCTION__, opaque);
    VlcWorker* obj = (VlcWorker*)opaque;
//    *planes = m_videobuf;
    planes[0] = m_videobuf;
    planes[1] = m_videobuf + m_width * m_height;
    planes[2] = m_videobuf + m_width * m_height * 5 / 4;
    printf("%s planes: [%p ,%p ,%p]\n", __FUNCTION__, planes[0], planes[1], planes[2]);
    return m_videobuf;
}

static void video_unlock_cb(void *opaque, void *picture, void *const *planes) {
    Q_UNUSED(opaque);
    Q_UNUSED(picture);
    Q_UNUSED(planes);
    printf("%s picture:%p planes:%p\n", __FUNCTION__, picture, planes);
    printf("%s planes: [%p ,%p ,%p]\n", __FUNCTION__, planes[0], planes[1], planes[2]);
//    VlcWrapper* obj = (VlcWrapper*)opaque;
//    QImage qimg((uchar*)planes, obj->m_frameWidth, obj->m_frameHeight, QImage::Format_ARGB32);

//    VlcWrapper* obj = (VlcWrapper*)opaque;
//    if(NULL != obj->vlcRenderCb) {
//        obj->vlcRenderCb->renderYUV((uchar*)picture, 1280, 738, 0);
//    }

    count++;

    printf("count: %d", count);
//    if(m_filename.isEmpty()) {
//        QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
//        m_filename = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".bin";
//    }
//    writeFile(m_filename, (char*)picture, m_videobuf_size);


    if(count == 100 || count == 200 || count == 300 || count == 400) {
        QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".bin";
        writeFile(fileName, (char*)picture, m_videobuf_size);
    }
}

static void video_display_cb(void *opaque, void *picture) {
    printf("render_cb %s opaque:%p picture:%p\n", __FUNCTION__, opaque, picture);
    VlcWorker* obj = (VlcWorker*)opaque;
    if(NULL != picture) {
        printf("picture: %p", picture);
//        QImage qimg((uchar*)picture, obj->m_frameWidth, obj->m_frameHeight, QImage::Format_ARGB32);
//        if(NULL != obj->vlcRenderCb) {
//            obj->vlcRenderCb->onRender(qimg);
//        }
    }
}


//typedef unsigned (*libvlc_video_format_cb)(void **opaque, char *chroma,
//                                           unsigned *width, unsigned *height,
//                                           unsigned *pitches,
//                                           unsigned *lines);
static unsigned video_format_cb(void **opaque, char *chroma,
                         unsigned *width, unsigned *height,
                         unsigned *pitches,
                         unsigned *lines) {
    printf("%s opaque:%p(%p) chroma:%s (%d x %d)\n", __FUNCTION__, opaque, *opaque, chroma, *width, *height);
    printf("%s picture:%p(%d) lines:%p(%d)\n", __FUNCTION__, pitches, *pitches, lines, *lines);

    m_width = *width;
    m_height = *height;
//    std::string format = "RV32";
//    memcpy(chroma, format.c_str(), 4);
//    m_videobuf_size = ((*width * *height) << 2);
//    m_videobuf = new char[m_videobuf_size];
//    memset(m_videobuf, 0x5e, m_videobuf_size);
//    *pitches = (*width) << 2;
//    *lines = *height;
//    printf("%s m_videobuf:%p\n", __FUNCTION__, m_videobuf);
//    return 1;

    strncpy(chroma, "I420", 4);

    m_videobuf_size = ((*width * *height) * 3 / 2);
    m_videobuf = new char[m_videobuf_size];
    memset(m_videobuf, 0x5e, m_videobuf_size);
    *pitches = (*width) * 3 / 2;
    *lines = *height;
    printf("%s m_videobuf:%p\n", __FUNCTION__, m_videobuf);

    return 3;

//    if(strcmp(chroma, "I420") == 0) {
//        printf("it is I420");
//        return 1;
//    } else {
//        return 0;
//    }
}
/**
 * Callback prototype to configure picture buffers format.
 *
 * \param opaque private pointer as passed to libvlc_video_set_callbacks()
 *               (and possibly modified by @ref libvlc_video_format_cb) [IN]
 */
//typedef void (*libvlc_video_cleanup_cb)(void *opaque);
static void video_cleanup_cb(void *opaque) {
    printf("video_cleanup_cb %s opaque:%p\n", __FUNCTION__, opaque);
    SAFE_DELETE_ARRAY(m_videobuf);
}


VlcWorker::VlcWorker(const QString& inputsrc, QObject *parent) : inputSource(inputsrc)
{
    printf("VlcWorker.this: %p", this);
    initVlc();
}

VlcWorker::~VlcWorker() {
    deinitVlc();
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
    libvlc_video_set_callbacks(m_vlcMediaPlayer, video_lock_cb, video_unlock_cb, video_display_cb, this);
    libvlc_video_set_format_callbacks(m_vlcMediaPlayer, video_format_cb, video_cleanup_cb);

    state = libvlc_media_player_get_state(m_vlcMediaPlayer);
    if (state == libvlc_Playing)
    {
        return;
    }

    libvlc_media_player_play(m_vlcMediaPlayer);
    while (state == libvlc_NothingSpecial || state == libvlc_Opening)
    {
        state = libvlc_media_player_get_state(m_vlcMediaPlayer);
        printf("current state: %d", state);
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
                    printf("resolution: %d x %d", tracks[i]->video->i_width, tracks[i]->video->i_height);
                    bFindResolution = true;
                    break;
                }
            }
        }

        libvlc_media_tracks_release(tracks, tracksCount);
        MSleep(100);
    }
    printf("start done.");

//     [workaround]: I don't know how to change format (libvlc_video_set_format) after playing...
//     reconnect the stream

//    libvlc_media_player_stop(m_vlcMediaPlayer);
//    libvlc_video_set_format(m_vlcMediaPlayer, "RV32", m_frameWidth, m_frameHeight, m_frameWidth << 2);
//    m_videobuf_size = (m_frameWidth * m_frameHeight) << 2;
//    m_videobuf = new char[(m_frameWidth * m_frameHeight) << 2];
//    libvlc_media_player_play(m_vlcMediaPlayer);
}
void VlcWorker::onStop() {
    printf("%s() : %p", __FUNCTION__, QThread::currentThreadId());
//    QThread::sleep(10);
//    printf("out %s() : %p", __FUNCTION__, QThread::currentThreadId());
    emit stopped();
}
void VlcWorker::onPause() {
    printf("%s() : %p", __FUNCTION__, QThread::currentThreadId());
}
void VlcWorker::onResume() {
    printf("%s() : %p", __FUNCTION__, QThread::currentThreadId());
}
void VlcWorker::onExit() {
    printf("%s() : %p", __FUNCTION__, QThread::currentThreadId());
}
