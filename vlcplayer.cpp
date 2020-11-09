#include "vlcplayer.h"
#include "ui_vlcplayer.h"
#include "Util.h"
#include "common.h"
#include "vlc/vlc.h"
#include "vlcwrapper.h"
#include <QScreen>
#include "videorender.h"

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
    videoView = new VideoRender();
    QPalette pal(videoView->palette());
    pal.setColor(QPalette::Background, QColor(200,200,200)); //设置背景黑色
    videoView->setAutoFillBackground(true);
    videoView->setPalette(pal);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(videoView);

    setLayout(layout);


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
    libvlc_media_release(vlcMedia);

    //vlcplayer和Qt控件关联
    libvlc_media_player_set_hwnd(m_vlcMediaPlayer, (void*)(videoView->winId()));
    libvlc_media_player_play(m_vlcMediaPlayer);

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
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(videoView->winId());
    return pixmap;
}

