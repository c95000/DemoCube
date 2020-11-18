#include "firstwindow.h"
#include <QVBoxLayout>

FirstWindow::FirstWindow(QWidget *parent) : QMainWindow(parent)
{
//    videoView = new GLVideoWidget();
    ffplayer = new FFPlayer();
    cameraController = new CameraController1();

    QVBoxLayout *vLayout = new QVBoxLayout(this);

    vLayout->addWidget(ffplayer, 4);
    vLayout->addWidget(cameraController, 1);
//    vLayout->addWidget(new QLabel("test"));


    QWidget *centerWindow = new QWidget;
    setCentralWidget(centerWindow);
    centerWindow->setLayout(vLayout);

    resize(QSize(640, 580));

    connect(cameraController, SIGNAL(signalConnect(const QString&)), ffplayer, SLOT(play(const QString&)));
    connect(cameraController, SIGNAL(signalDisconnect()), ffplayer, SLOT(stop()));
    connect(cameraController, SIGNAL(play()), ffplayer, SLOT(play()));
    connect(cameraController, SIGNAL(pause()), ffplayer, SLOT(pause()));
    connect(cameraController, SIGNAL(takePicture()), ffplayer, SLOT(takePicture()));
    connect(cameraController, SIGNAL(comment()), this, SLOT(on_btnComment()));

    connect(ffplayer, SIGNAL(played()), cameraController, SLOT(played()));
    connect(ffplayer, SIGNAL(paused()), cameraController, SLOT(paused()));
    connect(ffplayer, SIGNAL(stopped()), cameraController, SLOT(stopped()));


    connect(cameraController, SIGNAL(startRecord()), ffplayer, SLOT(startRecord()));
    connect(cameraController, SIGNAL(stopRecord()), ffplayer, SLOT(stopRecord()));
    connect(ffplayer, SIGNAL(startRecorded()), cameraController, SLOT(startRecorded()));
    connect(ffplayer, SIGNAL(stopRecorded()), cameraController, SLOT(stopRecorded()));

    connect(cameraController, SIGNAL(zoomin()), this, SLOT(onZoomin()));
    connect(cameraController, SIGNAL(zoomout()), this, SLOT(onZoomout()));
}

FirstWindow::~FirstWindow() {

    delete ffplayer;
    delete cameraController;
}


void FirstWindow::onZoomin() {
    printf("onZoomin");
}
void FirstWindow::onZoomout() {
    printf("onZoomout");
}
