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
//    connect(controller, SIGNAL(stop()), worker, SLOT(onStop()));
    connect(controller, SIGNAL(exit()), worker, SLOT(onExit()));

    connect(controller, SIGNAL(stop()), this, SLOT(onStop()));

    controller->setMaximumHeight(80);

    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(m_videoView, 5);
    layout->addWidget(controller, 1);

    setLayout(layout);

    childThread = new QThread();

    loading = new Loading(this);
    loading->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    loading->setWindowModality(Qt::ApplicationModal);
    loading->resize(256, 256);
    loading->start();
//    loading->show();

    connect(controller, SIGNAL(stop()), loading, SLOT(show()));

    worker->moveToThread(childThread);
    connect(childThread, SIGNAL(started()), worker, SLOT(onStop()));
    connect(worker, &VlcWorker::stopped, [=](){
        printf("VlcWorker stopped: %p", QThread::currentThreadId());
        childThread->quit();
    });
    connect(childThread, &QThread::finished, [=](){
        printf("childThread finished %p", QThread::currentThreadId());
    });
    connect(childThread, SIGNAL(finished()), loading, SLOT(close()));
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
//    loading->show();
//    Loading *loading = new Loading(this);
//    loading->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    loading->setWindowModality(Qt::ApplicationModal);
//    loading->resize(256, 256);
//    loading->start();
//    loading->show();

//    connect(worker, &VlcWorker::stopped, [=](){
//        printf("stopped signal....");
//        loading->close();
//        delete loading;
//    });
}

void VlcPlayer::onStop() {
    printf("VlcPlayer::%s():%p", __FUNCTION__, QThread::currentThreadId());
//    Loading *loading = new Loading(this);
//    loading->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    loading->setWindowModality(Qt::ApplicationModal);
//    loading->resize(256, 256);
//    loading->start();
//    loading->show();

//    connect(worker, &VlcWorker::stopped, [=](){
//        printf("stopped signal....%p", QThread::currentThreadId());
//        loading->close();
//    });
//    printf("x VlcPlayer::%s():%p", __FUNCTION__, QThread::currentThreadId());

//    worker->moveToThread(childThread);
//    childThread->start();
//    connect(childThread, SIGNAL(started()), worker, SLOT(onStop()));

//    Loading *loading = new Loading(this);
//    loading->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    loading->setWindowModality(Qt::ApplicationModal);
//    loading->resize(256, 256);
//    loading->start();
//    loading->show();

//    QTimer *myTimer = new QTimer(this);
//    myTimer->start(1000*5);
//    connect(myTimer,&QTimer::timeout,[=](){

//            myTimer->stop();
//            loading->close();
//            delete loading;
//            delete myTimer;
//        });


//    printf("test");



    childThread->start();
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
