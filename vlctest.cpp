#include "vlctest.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include "common.h"
#include <QFileDialog>
#include <QMessageBox>
#include "Util.h"
#include <stdio.h>
#include <stdarg.h>

static int m_videobuf_size = 0;
static int m_width;
static int m_height;
static char* m_videobuf = NULL;
static int count = 0;

static void writeFile(const QString& filename, const char* data, int size) {
    QFile f(filename);
    f.open(QIODevice::WriteOnly | QIODevice::Append);
    f.write(data, size);
    f.close();
}

static void *video_lock_cb(void *opaque, void **planes) {
    //        printf("%s opaque:%p planes:%p  *planes:%p\n", __FUNCTION__, opaque, planes, *planes);

    planes[0] = m_videobuf;
    planes[1] = m_videobuf + m_width * m_height;
    planes[2] = m_videobuf + m_width * m_height * 5 / 4;
    //    printf("%s planes: [%p ,%p ,%p]", __FUNCTION__, planes[0], planes[1], planes[2]);
    return m_videobuf;
}

static void video_unlock_cb(void *opaque, void *picture, void *const *planes) {
    //        printf("%s opaque: %p  picture: %p plances: %p\n", __FUNCTION__, opaque, picture, planes);


    Q_UNUSED(opaque);
    Q_UNUSED(picture);
    Q_UNUSED(planes);
}

static void video_display_cb(void *opaque, void *picture) {
    //    printf("%s opaque:%p picture:%p", __FUNCTION__, opaque, picture);
    VlcTest* obj = static_cast<VlcTest*>(opaque);
    if(nullptr != obj->videoView) {
        //        obj->updatePts(count++);
        QByteArray ba;
        ba.append((char *)picture, m_videobuf_size);
        obj->videoView->setFrameData(ba);
        obj->updatePos();
    }

    //    count++;
    //    if(count % 100 == 0) {
    //        printf("%s opaque: %p  picture: %p\n", __FUNCTION__, opaque, picture);
    //        QByteArray ba;
    //        ba.append((char *)picture, m_videobuf_size);
    //        QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    //        QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".bin";
    //        writeFile(fileName, (char*)ba.data(), ba.size());
    //    }
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
    printf("%s pitches:%p(%d) lines:%p(%d)\n", __FUNCTION__, pitches, *pitches, lines, *lines);
    //    count = 0;
    //    VlcPlayer* obj = static_cast<VlcPlayer*>(*opaque);
    //    if(nullptr != obj) {
    //        printf("obj->videoView: %p", obj->videoView);
    //        obj->videoView->setYUV420pParameters(*width, *height);
    //    }

    VlcTest* obj = static_cast<VlcTest*>(*opaque);
    if(nullptr != obj && nullptr != obj->videoView) {
        printf("obj->videoView: %p", obj->videoView);
        obj->videoView->setYUV420pParameters(*width, *height);
    }

    m_width = *width;
    m_height = *height;
    strncpy(chroma, "I420", 4);

    SAFE_DELETE_ARRAY(m_videobuf);
    m_videobuf_size = ((*width * *height) * 3 / 2);
    m_videobuf = new char[m_videobuf_size];
    memset(m_videobuf, 0x5e, m_videobuf_size);
    pitches[0] = *width;
    pitches[1] = *width/2;
    pitches[2] = *width/2;

    lines[0] = *height;
    lines[1] = *height/2;
    lines[2] = *height/2;
    printf("%s m_videobuf:%p\n", __FUNCTION__, m_videobuf);

    return 3;
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

//typedef void (*libvlc_log_cb)(void *data, int level, const libvlc_log_t *ctx,
//                              const char *fmt, va_list args);
static void vlc_log_cb(void *data, int level, const libvlc_log_t *ctx,
                       const char *fmt, va_list args) {
    //    printf("%s level: %d\n", __FUNCTION__, level);

    //    printf("%s", fmt);
    //    int ret = vprintf(fmt, args);
    //    printf("ret: %d", ret);

    QString log = QString::vasprintf(fmt, args);
    printf("---------- %s", log.toStdString().c_str());

    //    char ch;
    //    while(ch = *(fmt++)) {
    //        if(ch == '%') {
    //            ch = *(fmt++);
    //            if(ch == 's') {
    //                char *str = va_arg(args, char *);
    //                printf("------- %s", str);
    //            } else if(ch == 'd') {
    //                int iValue = va_arg(args, int);
    //                printf("------- %d", iValue);
    //            } else {
    //                printf("------- %c", ch);
    //            }
    //        } else {

    //        }
    //    }
}

VlcTest::VlcTest(QWidget *parent) : QWidget(parent)
{
    QPushButton *btnOpen, *btnPlay, *btnPause, *btnStop, *btnTest;

    btnOpen = new QPushButton(this);
    btnOpen->setText(tr("open"));

    btnPlay = new QPushButton(this);
    btnPlay->setText(tr("play"));

    btnPause = new QPushButton(this);
    btnPause->setText(tr("pause"));

    btnStop = new QPushButton(this);
    btnStop->setText(tr("stop"));

    btnTest = new QPushButton(this);
    btnTest->setText(tr("test"));

    videoView = new GLVideoWidget(this);

    QGridLayout *pg=new QGridLayout;

    pg->addWidget(videoView, 0, 0, 1, -1);

    pg->addWidget(btnOpen, 1, 0, 1,1);
    pg->addWidget(btnPlay, 1, 1, 1,1);
    pg->addWidget(btnPause, 1, 2, 1,1);
    pg->addWidget(btnStop, 1, 3, 1,1);
    pg->addWidget(btnTest, 1, 4, 1,1);

    setLayout(pg);

    pg->setRowMinimumHeight(0, 260);
    pg->setRowStretch(0, 1);
    printf("rows: %d columns: %d", pg->rowCount(), pg->columnCount());

    connect(btnOpen, &QPushButton::clicked, [=]() {
        printf("btnOpen");
        QString videoPath = Configure::getInstance()->getVideopath();
        QString filename = QFileDialog::getOpenFileName(this,tr("action"),videoPath,"",0);
        if(filename.isEmpty()) {
            return;
        }

        printf("filename: %s", filename.toStdString().c_str());
        fileName = filename.replace("/", "\\");
        printf("fileName: %s", fileName.toStdString().c_str());

        play();
    });

    connect(btnPlay, &QPushButton::clicked, [=]() {
        printf("btnPlay");
        play();
    });

    connect(btnPause, &QPushButton::clicked, [=]() {
        printf("btnPause");
        pause();
    });

    connect(btnStop, &QPushButton::clicked, [=]() {
        printf("btnStop");
        stop();
    });

    connect(btnTest, &QPushButton::clicked, [=]() {
        printf("btnTest");
        test();
    });

    m_vlcInstance = libvlc_new(0, NULL);
    m_vlcMediaPlayer = NULL;

    //判断vlc实例化是否ok
    if (m_vlcInstance == NULL)
    {
        QMessageBox::critical(this, "错误", "error(1-101)");
        exit(-1);
    }

    libvlc_log_set(m_vlcInstance, vlc_log_cb, this);

    printf("VlcTest: %p", this);

    fileName = tr("C:\\Users\\201708\\Videos\\eb3aa50943c201336de9fa1c23b5a6c5-480p.mp4");

}

VlcTest::~VlcTest() {
    libvlc_media_release(m_vlcMedia);
    libvlc_media_player_stop(m_vlcMediaPlayer);
    libvlc_media_player_release(m_vlcMediaPlayer);
    libvlc_release(m_vlcInstance);
}

void VlcTest::play() {
    if(fileName.isNull() || fileName.isEmpty()) {
        QMessageBox::critical(this, "please open media file", "error(1-101)");
        return;
    }

    /* Stop if something is playing */
    if (nullptr != m_vlcMediaPlayer)
    {
        libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
        printf("current state: %d", state);
        stop();
    }

    libvlc_media_t *vlcMedia = libvlc_media_new_path(m_vlcInstance, fileName.toStdString().c_str());
    if (!vlcMedia)
    {
        printf("play failed.");
        return;
    }

    m_vlcMediaPlayer = libvlc_media_player_new_from_media(vlcMedia);
    //    libvlc_media_player_set_media(m_vlcMediaPlayer, vlcMedia);

    libvlc_video_set_callbacks(m_vlcMediaPlayer, video_lock_cb, video_unlock_cb, video_display_cb, this);
    libvlc_video_set_format_callbacks(m_vlcMediaPlayer, video_format_cb, video_cleanup_cb);

    libvlc_media_player_play(m_vlcMediaPlayer);

    while (true)
    {
        libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
        printf("current state: %d", state);

        if(libvlc_Playing == state) {
            libvlc_time_t duration = libvlc_media_get_duration(vlcMedia);
            printf("current duration: %lld", duration);
            float fps = libvlc_media_player_get_fps(m_vlcMediaPlayer);
            printf("current fps: %f", fps);
            //                emit updateProgress(0, (int)duration);

            libvlc_media_release(vlcMedia);
            break;
        }
        MSleep(1000);
    }

}
void VlcTest::pause() {
    if (!m_vlcMediaPlayer) {
        return;
    }
    libvlc_media_player_pause(m_vlcMediaPlayer);
    //    if (libvlc_media_player_is_playing(m_vlcMediaPlayer))
    //    {
    //        /* Pause */
    //        printf(("NEXT  libvlc_media_player_pause()"));
    //        libvlc_media_player_pause(m_vlcMediaPlayer);
    //    }
    //    else
    //    {
    //        /* Play again */
    //        printf(("NEXT  libvlc_media_player_play()"));
    //        libvlc_media_player_play(m_vlcMediaPlayer);
    //    }
}
void VlcTest::stop() {
    if (m_vlcMediaPlayer)
    {
        QMutexLocker locker(&mutex);
        printf("stop -----------0");
        printf("stop -----------1");
        libvlc_media_player_stop(m_vlcMediaPlayer);
        printf("stop -----------2");
        while (true)
        {
            libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
            printf("current state: %d", state);
            if(libvlc_Playing != state) {
                break;
            }
            MSleep(1000);
        }

        /* release the media player */
        libvlc_media_player_release(m_vlcMediaPlayer);
        m_vlcMediaPlayer = nullptr;
    }
}

void VlcTest::test() {
    QMutexLocker locker(&mutex);
    if (m_vlcMediaPlayer) {
        int value = libvlc_media_player_is_playing(m_vlcMediaPlayer);
        printf("vxlxxxue: %d threadId: %d", value, QThread::currentThreadId());
    }
}


void VlcTest::updatePos() {
    frameCount ++;
    if(frameCount % 30 == 0) {
        if (m_vlcMediaPlayer && libvlc_media_player_is_playing(m_vlcMediaPlayer))
        {
            printf("updatePos --- 1");
            float pos = libvlc_media_player_get_position(m_vlcMediaPlayer); //pos  is 0.01~0.99 1.0
            printf("%s playing pos: %f", __FUNCTION__, pos);
            printf("updatePos --- 2");
        }


    }
    //    printf("threadId: %d", QThread::currentThreadId());
    //    mutex.tryLock(0);

    //    mutex.unlock();

    //    if(mutex.tryLock()) {
    //        if (m_vlcMediaPlayer && libvlc_media_player_is_playing(m_vlcMediaPlayer))
    //        {
    //            printf("updatePos --- 1");
    //            float pos = libvlc_media_player_get_position(m_vlcMediaPlayer); //pos  is 0.01~0.99 1.0
    //            if(frameCount % 30 == 0) {
    //                printf("%s playing pos: %f", __FUNCTION__, pos);
    //            }
    //            printf("updatePos --- 2");
    //        }
    //    }

    //    mutex.unlock();
}
