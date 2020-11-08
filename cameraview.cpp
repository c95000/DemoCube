#include "cameraview.h"
#include "common.h"
#include <QMessageBox>
#include <QGuiApplication>
#include <QScreen>
#include <QThread>

CameraView::CameraView(QWidget *parent) : QWidget(parent)
{
    videoView = new QLabel();
    QPalette pal(videoView->palette());
    pal.setColor(QPalette::Background, QColor(128,128,128)); //设置背景黑色
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
}

CameraView::~CameraView() {
    stop();
    libvlc_media_release(m_vlcMedia);
    libvlc_media_player_stop(m_vlcMediaPlayer);
    libvlc_media_player_release(m_vlcMediaPlayer);
    libvlc_release(m_vlcInstance);
}

void CameraView::onConnect(const QString& sourceUrl) {
    printf("%s() url: %s", __FUNCTION__, sourceUrl.toStdString().c_str());
    this->sourceUrl = sourceUrl;
    play(sourceUrl);
}

void CameraView::onDisconnect() {
    printf("%s()", __FUNCTION__);
    stop();
}

void CameraView::pause() {
    if (m_vlcMediaPlayer)
    {
        libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
        if(libvlc_Playing == state) {
            libvlc_media_player_pause(m_vlcMediaPlayer);
            emit paused();
        }
    }
}

void CameraView::play() {
    play(sourceUrl);
}

void CameraView::takePicture() {
    printf("VlcPlayer::%s():%p", __FUNCTION__, QThread::currentThreadId());
    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".png";
    printf("filename: %s", fileName.toStdString().c_str());
    if (fileName.length() > 0)
    {
        snapshot().save(fileName);
    }
}

const QPixmap CameraView::snapshot() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(videoView->winId());
    return pixmap;
}

void CameraView::play(const QString& inputSrc) {
    if (m_vlcMediaPlayer)
    {
        printf("stop mediaplayer");
        stop();
    }

    QString inputSource = inputSrc;

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

    libvlc_media_t *vlcMedia = libvlc_media_new_location(m_vlcInstance, inputSource.toStdString().c_str());
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

void CameraView::stop() {
    if (m_vlcMediaPlayer)
    {
        libvlc_media_player_stop(m_vlcMediaPlayer);
        libvlc_media_player_release(m_vlcMediaPlayer);
        m_vlcMediaPlayer = NULL;
    }

    emit stopped();
}
