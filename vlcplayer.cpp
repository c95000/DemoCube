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
    videoView = new QLabel("test");
    QLabel* temp = dynamic_cast<QLabel*>(videoView);
//    temp->resize(100, 100);
//    temp->setAlignment(Qt::AlignCenter);
//    videoView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QPalette pal(videoView->palette());
    pal.setColor(QPalette::Background, QColor(255,255,255)); //设置背景黑色
    videoView->setAutoFillBackground(true);
    videoView->setPalette(pal);

//    videoView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

//    controller = new VlcPlayerController();
//    connect(controller, SIGNAL(play()), this, SLOT(play()));
//    connect(controller, SIGNAL(stop()), this, SLOT(stop()));
//    connect(controller, SIGNAL(pause()), this, SLOT(pause()));
//    connect(controller, SIGNAL(exit()), this, SLOT(close()));
//    connect(controller, SIGNAL(takePicture()), this, SLOT(takePicture()));
//    connect(controller, SIGNAL(comment()), this, SLOT(comment()));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
//    layout->addStretch(1);
    layout->addWidget(videoView, 0, Qt::AlignCenter);
//    layout->addStretch(1);

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

void VlcPlayer::resizeEvent(QResizeEvent *event) {
//videoView->setFixedSize(100, 100);
//    printf("old size: %d x %d", event->oldSize().width(), event->oldSize().height());
    printf("size: %d x %d", event->size().width(), event->size().height());

    QSize videoSize = QSize(100, 100);//videoView->size();
    QSize size = event->size().scaled(videoSize, Qt::KeepAspectRatio);
    printf("new size: %d x %d", size.width(), size.height());

//    QSize size = event->size().scaled(QSize(100, 200), Qt::KeepAspectRatio);
    videoView->resize(size);
//    QSize size = matrix(event->size(), QSize(100, 200));

//    QSize size = viewStack->size();
//    printf("viewStack: %d x %d", size.width(), size.height());

//    double ratio = 1.0 * size.width() / size.height();

//    int wx = size.height() * 16 / 9;

//    if(wx > size.width()) {
//        int wh = size.width() * 9 / 16;
//        viewStack->resize(size.width(), wh);
//        printf("viewStack: %d x %d", size.width(), wh);
//    }
//    else {
//        viewStack->setFixedSize(wx, size.height());
//        printf("viewStack: %d x %d", wx, size.height());
//    }
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

