#include "vlcplayer.h"
#include "ui_vlcplayer.h"
#include "Util.h"
#include "common.h"
#include "vlc/vlc.h"
#include "vlcwrapper.h"
#include <QScreen>
#include "videorender.h"
#include "glvideowidget.h"


static void writeFile(const QString& filename, const char* data, int size) {
    QFile f(filename);
    f.open(QIODevice::WriteOnly | QIODevice::Append);
    f.write(data, size);
    f.close();
}

//QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
//QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".yuv";
//writeFile(fileName, buf, pCodecCtx->height * pCodecCtx->width * 3 / 2);

static QString m_filename;
static int m_videobuf_size = 0;
static int m_width;
static int m_height;
static char* m_videobuf = NULL;
static int count = 0;

static void *video_lock_cb(void *opaque, void **planes) {
//    printf("%s opaque:%p\n", __FUNCTION__, opaque);
    VlcPlayer* obj = (VlcPlayer*)opaque;
    planes[0] = m_videobuf;
    planes[1] = m_videobuf + m_width * m_height;
    planes[2] = m_videobuf + m_width * m_height * 5 / 4;
//    printf("%s planes: [%p ,%p ,%p]", __FUNCTION__, planes[0], planes[1], planes[2]);
    return m_videobuf;
}

static void video_unlock_cb(void *opaque, void *picture, void *const *planes) {
    Q_UNUSED(opaque);
    Q_UNUSED(picture);
    Q_UNUSED(planes);
//    printf("%s picture:%p planes:%p\n", __FUNCTION__, picture, planes);
//    printf("%s planes: [%p ,%p ,%p]", __FUNCTION__, planes[0], planes[1], planes[2]);
//    VlcWrapper* obj = (VlcWrapper*)opaque;
//    QImage qimg((uchar*)planes, obj->m_frameWidth, obj->m_frameHeight, QImage::Format_ARGB32);

//    VlcWrapper* obj = (VlcWrapper*)opaque;
//    if(NULL != obj->vlcRenderCb) {
//        obj->vlcRenderCb->renderYUV((uchar*)picture, 1280, 738, 0);
//    }



//    printf("count: %d", count);
//    if(m_filename.isEmpty()) {
//        QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
//        m_filename = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".bin";
//    }
//    writeFile(m_filename, (char*)picture, m_videobuf_size);


//    if(count % 300 == 0) {
//        QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
//        QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".bin";
//        writeFile(fileName, (char*)picture, m_videobuf_size);
//    }
}

static void video_display_cb(void *opaque, void *picture) {
//    printf("%s opaque:%p picture:%p", __FUNCTION__, opaque, picture);
    count++;

    VlcPlayer* obj = static_cast<VlcPlayer*>(opaque);
    if(nullptr != obj->videoView) {
        QByteArray ba;
        ba.append((char *)picture, m_videobuf_size);
        obj->videoView->setFrameData(ba);
//        if(count % 250 == 0) {
//            QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
//            QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".bin";
//            writeFile(fileName, (char*)ba.data(), ba.size());
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
    printf("%s pitches:%p(%d) lines:%p(%d)\n", __FUNCTION__, pitches, *pitches, lines, *lines);

    VlcPlayer* obj = static_cast<VlcPlayer*>(*opaque);
    if(nullptr != obj) {
        printf("obj->videoView: %p", obj->videoView);
        obj->videoView->setYUV420pParameters(*width, *height);
    }

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




VlcPlayer::VlcPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VlcPlayer)
{
    init();
}

VlcPlayer::VlcPlayer(const QString& inputSrc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VlcPlayer),
    inputSource(inputSrc)
{
    ui->setupUi(this);

    init();
}

VlcPlayer::~VlcPlayer()
{
    stop();
    libvlc_media_release(m_vlcMedia);
    libvlc_media_player_stop(m_vlcMediaPlayer);
    libvlc_media_player_release(m_vlcMediaPlayer);
    libvlc_release(m_vlcInstance);

    delete ui;
}

void VlcPlayer::init() {
//    videoView = new QLabel("test", this);
//    videoView = new VideoRender(this);
    videoView = new GLVideoWidget(this);

    // opengl cancel pal setting.
//    QPalette pal(videoView->palette());
//    pal.setColor(QPalette::Background, QColor(200,200,200)); //设置背景黑色
//    videoView->setAutoFillBackground(true);
//    videoView->setPalette(pal);

//    QHBoxLayout *layout = new QHBoxLayout();
//    layout->setAlignment(Qt::AlignCenter);
//    layout->setContentsMargins(0, 0, 0, 0);
//    layout->addStretch();
//    layout->addWidget(videoView);
//    layout->addStretch();

//    setLayout(layout);

    //创建vlc实例
    m_vlcInstance = libvlc_new(0, NULL);
    m_vlcMediaPlayer = NULL;

    //判断vlc实例化是否ok
    if (m_vlcInstance == NULL)
    {
        QMessageBox::critical(this, "错误", "error(1-101)");
        exit(-1);
    }

    if(!inputSource.isNull() && !inputSource.isEmpty()) {
        play();
    }
}

void VlcPlayer::play(const QString& inputSrc) {
    printf("VlcPlayer::%s(inputSrc: %s) %p", __FUNCTION__, inputSrc.toStdString().c_str(), QThread::currentThreadId());
    inputSource = inputSrc;
    //如果视频正在播放，先停止播放
//    if (m_vlcMediaPlayer && libvlc_media_player_is_playing(m_vlcMediaPlayer))
    if (m_vlcMediaPlayer)
    {
        printf("stop mediaplayer");
        stop();
    }

    play();
}

void VlcPlayer::play() {
    printf("VlcPlayer::%s():%p", __FUNCTION__, QThread::currentThreadId());

    QString fileName = inputSource.replace("/", "\\");

    setWindowTitle(fileName);

    //It is paused.
    if (m_vlcMediaPlayer)
    {
        libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
        if(libvlc_Paused == state) {
            libvlc_media_player_play(m_vlcMediaPlayer);
            emit played();
        }
        return;
    }



    libvlc_media_t *vlcMedia = libvlc_media_new_path(m_vlcInstance, fileName.toStdString().c_str());
    if (!vlcMedia)
    {
        printf("play failed.");
        return;
    }

    m_vlcMediaPlayer = libvlc_media_player_new_from_media(vlcMedia);

    libvlc_media_player_set_media(m_vlcMediaPlayer, vlcMedia);
    libvlc_video_set_callbacks(m_vlcMediaPlayer, video_lock_cb, video_unlock_cb, video_display_cb, this);
    libvlc_video_set_format_callbacks(m_vlcMediaPlayer, video_format_cb, video_cleanup_cb);

    //vlcplayer和Qt控件关联
//    libvlc_media_player_set_hwnd(m_vlcMediaPlayer, (void*)(videoView->winId()));
    libvlc_media_player_play(m_vlcMediaPlayer);

    while (true)
    {
        libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
        printf("current state: %d", state);
        if(libvlc_Playing == state) {
            break;
        }
        MSleep(100);
    }

    printf("play ok.");
    emit played();
}


void VlcPlayer::pause() {
    printf("VlcPlayer::%s():%p", __FUNCTION__, QThread::currentThreadId());
    if (m_vlcMediaPlayer)
    {
        libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
        if(libvlc_Playing == state) {
            libvlc_media_player_pause(m_vlcMediaPlayer);
            emit paused();
        }
    }

}

void VlcPlayer::stop() {

    if (m_vlcMediaPlayer)
    {
        libvlc_media_player_stop(m_vlcMediaPlayer);
        libvlc_media_player_release(m_vlcMediaPlayer);
        m_vlcMediaPlayer = NULL;
    }

    emit stopped();
}

void VlcPlayer::close() {
    printf("VlcPlayer::%s():%p", __FUNCTION__, QThread::currentThreadId());
}

void VlcPlayer::takePicture() {
    printf("VlcPlayer::%s():%p", __FUNCTION__, QThread::currentThreadId());
    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".png";
    printf("filename: %s", fileName.toStdString().c_str());
    if (fileName.length() > 0)
    {
        snapshot().save(fileName);
    }
}

void VlcPlayer::comment() {
//    printf("VlcPlayer::%s():%p", __FUNCTION__, QThread::currentThreadId());
//    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
//    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".png";
//    printf("filename: %s", fileName.toStdString().c_str());
//    if (fileName.length() > 0)
//    {
//        QScreen *screen = QGuiApplication::primaryScreen();
//        QPixmap pixmap = screen->grabWindow(videoView->winId());
//        pixmap.save(fileName);
//    }
}

const QPixmap VlcPlayer::snapshot() {
    QImage img = videoView->grabFramebuffer();
    return QPixmap::fromImage(img);
//    QScreen *screen = QGuiApplication::primaryScreen();
//    QPixmap pixmap = screen->grabWindow(videoView->winId());
//    return pixmap;
}

void VlcPlayer::resizeEvent(QResizeEvent *event) {
    printf("VlcPlayer resizeEvent: %d x %d", event->size().width(), event->size().height());
    QSizeF parentSize = parentWidget()->size();
    QSizeF destSz = QSizeF(16, 9).scaled(parentSize, Qt::KeepAspectRatio);
    videoView->resize(QSize(round(destSz.width()), round(destSz.height())));

    QSize psz = size();
    QPoint center((psz.width() - destSz.width())/2, (psz.height() - destSz.height())/2);
    videoView->move(center);
}

void VlcPlayer::showEvent(QShowEvent *event) {
    printf("VlcPlayer showEvent");
    printf("VlcPlayer showEvent: %d x %d", size().width(), size().height());
    QSizeF parentSize = parentWidget()->size();
    QSizeF destSz = QSizeF(16, 9).scaled(parentSize, Qt::KeepAspectRatio);
    videoView->resize(QSize(round(destSz.width()), round(destSz.height())));

    QSize psz = size();
    QPoint center((psz.width() - destSz.width())/2, (psz.height() - destSz.height())/2);
    videoView->move(center);

}

void VlcPlayer::hideEvent(QHideEvent *event) {
    printf("VlcPlayer hideEvent");
}
