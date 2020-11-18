#include "firstwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

FirstWindow::FirstWindow(QWidget *parent) : QMainWindow(parent)
{
//    videoView = new GLVideoWidget();
    ffplayer = new FFPlayer();
    cameraController = new CameraController1();
    arnetWrapper = new ArnetWrapper();
    socketTest = new SocketTest();

    QVBoxLayout *vLayout = new QVBoxLayout(this);

    vLayout->addWidget(ffplayer, 4);
    vLayout->addWidget(cameraController, 1);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addLayout(vLayout);
    hLayout->addWidget(socketTest);

    QWidget *centerWindow = new QWidget;
    setCentralWidget(centerWindow);
    centerWindow->setLayout(hLayout);

    resize(QSize(640, 580));

    connect(cameraController, SIGNAL(signalConnect(const QString&)), ffplayer, SLOT(play(const QString&)));
    connect(cameraController, SIGNAL(signalDisconnect()), ffplayer, SLOT(stop()));
    connect(cameraController, SIGNAL(play()), ffplayer, SLOT(play()));
    connect(cameraController, SIGNAL(pause()), ffplayer, SLOT(pause()));
    connect(cameraController, SIGNAL(takePicture()), ffplayer, SLOT(takePicture()));

    connect(ffplayer, SIGNAL(played()), cameraController, SLOT(played()));
    connect(ffplayer, SIGNAL(paused()), cameraController, SLOT(paused()));
    connect(ffplayer, SIGNAL(stopped()), cameraController, SLOT(stopped()));


    connect(cameraController, SIGNAL(startRecord()), ffplayer, SLOT(startRecord()));
    connect(cameraController, SIGNAL(stopRecord()), ffplayer, SLOT(stopRecord()));
    connect(ffplayer, SIGNAL(startRecorded()), cameraController, SLOT(startRecorded()));
    connect(ffplayer, SIGNAL(stopRecorded()), cameraController, SLOT(stopRecorded()));

    connect(cameraController, SIGNAL(signalConnect(const QString&)), arnetWrapper, SLOT(connect(const QString&)));
    connect(cameraController, SIGNAL(zoomin()), arnetWrapper, SLOT(zoomWide()));
    connect(cameraController, SIGNAL(zoomout()), arnetWrapper, SLOT(zoomTele()));

    connect(arnetWrapper, SIGNAL(error(int)), this, SLOT(onError(int)));
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

void FirstWindow::onError(int errorCode) {
    printf("errorcode : %d", errorCode);
    QMessageBox::critical(this, "错误", tr("error(%1)").arg(errorCode));
}
