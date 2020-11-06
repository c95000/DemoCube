#include "vlcplayer.h"
#include "ui_vlcplayer.h"
#include "Util.h"
#include "common.h"
#include "vlc/vlc.h"


VlcPlayer::VlcPlayer(const QString& inputSrc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VlcPlayer),
    inputSource(inputSrc)
{
    ui->setupUi(this);

    worker = new VlcWorker(inputSrc);

    m_videoView = new GLVideoWidget();
    controller = new VlcPlayerController();
//    connect(controller, SIGNAL(play()), this, SLOT(onPlay()));
    connect(controller, SIGNAL(play()), worker, SLOT(onPlay()));
    connect(controller, SIGNAL(pause()), worker, SLOT(onPause()));
    connect(controller, SIGNAL(stop()), worker, SLOT(onStop()));
    connect(controller, SIGNAL(exit()), worker, SLOT(onExit()));

    controller->setMaximumHeight(80);

    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(m_videoView, 5);
    layout->addWidget(controller, 1);

    setLayout(layout);

    childThread = new QThread();
    worker->moveToThread(childThread);
    childThread->start();
}

VlcPlayer::~VlcPlayer()
{
    childThread->exit();
    childThread->wait();
    delete childThread;

    delete worker;
    delete m_videoView;
    delete ui;
}


void VlcPlayer::onPlay() {
    printf("VlcPlayer::%s():%p", __FUNCTION__, QThread::currentThreadId());
}


void VlcPlayer::start() {



    emit started();
}

void VlcPlayer::stop() {

    emit stopped();
}

void VlcPlayer::pause() {

    emit paused();
}

void VlcPlayer::resume() {

    emit started();
}
