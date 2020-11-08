#include "cameracontroller1.h"

CameraController1::CameraController1(QWidget *parent) : QWidget(parent)
{
    init();
}

CameraController1::CameraController1(const QString& url, QWidget *parent) : QWidget(parent), sourceUrl(url)
{
    init();
}

CameraController1::~CameraController1() {

}

void CameraController1::init() {
    if(sourceUrl.isNull() || sourceUrl.isEmpty()) {
        sourceUrl = tr("rtsp://192.168.1.225/");
    }

    btnConnect = new QPushButton("连接");
    btnPlay = new QPushButton("播放");
    btnPlay->hide();
    btnPause = new QPushButton("暂停");
    btnDisconnect = new QPushButton("断开");
    btnTakePicture = new QPushButton("拍照");
    btnComment = new QPushButton("批注");
    btnExit = new QPushButton("退出");
    btnExit->hide();

//    btnPlay->setEnabled(false);
//    btnPause->setEnabled(false);
//    btnDisconnect->setEnabled(false);
//    btnTakePicture->setEnabled(false);
//    btnComment->setEnabled(false);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(btnConnect);
    hLayout->addWidget(btnPlay);
    hLayout->addWidget(btnPause);
    hLayout->addWidget(btnDisconnect);
    hLayout->addWidget(btnTakePicture);
    hLayout->addWidget(btnComment);
    hLayout->addStretch();

    setLayout(hLayout);

    connect(btnConnect, &QPushButton::clicked, this, [=]() {
        emit signalConnect(sourceUrl);
    });
    connect(btnDisconnect, SIGNAL(clicked(bool)), this, SIGNAL(signalDisconnect()));

    //    connect(btnStop, SIGNAL(clicked(bool)), this, SIGNAL(stop()));
    //    connect(btnTakePicture, SIGNAL(clicked(bool)), this, SIGNAL(takePicture()));
    //    connect(btnComment, SIGNAL(clicked(bool)), this, SIGNAL(comment()));
    //    connect(btnExit, SIGNAL(clicked(bool)), this, SIGNAL(close()));

    //    connect(btnOpen, SIGNAL(clicked(bool)), this, SLOT(onOpen()));
    //    connect(btnPlay, SIGNAL(clicked(bool)), this, SLOT(onPlay()));
    //    connect(btnPause, SIGNAL(clicked(bool)), this, SLOT(onPause()));

//    connect(btnConnect, SIGNAL(clicked(bool)), this, SLOT(onDisconnect()));
//    connect(btnDisconnect, SIGNAL(clicked(bool)), this, SLOT(onDisconnect()));
}

void CameraController1::onConnect(const QString& sourceUrl) {
    printf("%s() is called.", __FUNCTION__);
}
void CameraController1::onDisconnect() {
    printf("%s() is called.", __FUNCTION__);
}

