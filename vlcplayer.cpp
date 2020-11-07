#include "vlcplayer.h"
#include "ui_vlcplayer.h"
#include "Util.h"
#include "common.h"
#include "vlc/vlc.h"
#include "vlcwrapper.h"
#include <QScreen>

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

//    childThread = new QThread();

//    loading = new Loading(this);
//    loading->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    loading->setWindowModality(Qt::ApplicationModal);
//    loading->resize(256, 256);
//    loading->start();
//    loading->show();

//    connect(controller, SIGNAL(stop()), loading, SLOT(show()));

//    worker->moveToThread(childThread);
//    connect(childThread, SIGNAL(started()), worker, SLOT(onStop()));
//    connect(worker, &VlcWorker::stopped, [=](){
//        printf("VlcWorker stopped: %p", QThread::currentThreadId());
//        childThread->quit();
//    });
//    connect(childThread, &QThread::finished, [=](){
//        printf("childThread finished %p", QThread::currentThreadId());
//    });
//    connect(childThread, SIGNAL(finished()), loading, SLOT(close()));
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
    videoView = new QLabel();
    QPalette pal(videoView->palette());
    pal.setColor(QPalette::Background, QColor(20,20,20)); //设置背景黑色
    videoView->setAutoFillBackground(true);
    videoView->setPalette(pal);

    controller = new VlcPlayerController();
//    connect(controller, SIGNAL(play()), worker, SLOT(onPlay()));
//    connect(controller, SIGNAL(pause()), worker, SLOT(onPause()));
//    connect(controller, SIGNAL(stop()), worker, SLOT(onStop()));
//    connect(controller, SIGNAL(exit()), worker, SLOT(onExit()));

    connect(controller, SIGNAL(play()), this, SLOT(play()));
    connect(controller, SIGNAL(stop()), this, SLOT(stop()));
    connect(controller, SIGNAL(pause()), this, SLOT(pause()));
    connect(controller, SIGNAL(exit()), this, SLOT(close()));
    connect(controller, SIGNAL(takePicture()), this, SLOT(takePicture()));
    connect(controller, SIGNAL(comment()), this, SLOT(comment()));

//    connect(controller, SIGNAL(pause()), this, SLOT(onPause()));

    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(videoView, 5);
    layout->addWidget(controller, 1);

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
    inputSource = inputSrc;
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

    //如果视频正在播放，先停止播放
    if (m_vlcMediaPlayer && libvlc_media_player_is_playing(m_vlcMediaPlayer))
    {
        printf("stop mediaplayer");
        stop();
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

    controller->onPlay();
    printf("play ok.");
}


void VlcPlayer::pause() {
    printf("VlcPlayer::%s():%p", __FUNCTION__, QThread::currentThreadId());
    if (m_vlcMediaPlayer)
    {
        libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
        if(libvlc_Playing == state) {
            libvlc_media_player_pause(m_vlcMediaPlayer);
            controller->onPause();
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
    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".png";
    printf("filename: %s", fileName.toStdString().c_str());
    if (fileName.length() > 0)
    {
        QScreen *screen = QGuiApplication::primaryScreen();
        QPixmap pixmap = screen->grabWindow(videoView->winId());
        pixmap.save(fileName);
    }
}

void VlcPlayer::comment() {
    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".png";
    printf("filename: %s", fileName.toStdString().c_str());
    if (fileName.length() > 0)
    {
        QScreen *screen = QGuiApplication::primaryScreen();
        QPixmap pixmap = screen->grabWindow(videoView->winId());
        pixmap.save(fileName);
    }
}

