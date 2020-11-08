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
    btnRecord = new QPushButton("录制");
    btnComment = new QPushButton("批注");
    btnExit = new QPushButton("退出");
    btnExit->hide();

    btnPlay->setEnabled(false);
    btnPause->setEnabled(false);
    btnDisconnect->setEnabled(false);
    btnTakePicture->setEnabled(false);
    btnComment->setEnabled(false);

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
        btnConnect->setEnabled(false);
        emit signalConnect(sourceUrl);
    });
    connect(btnDisconnect, SIGNAL(clicked(bool)), this, SIGNAL(signalDisconnect()));

    connect(btnPlay, SIGNAL(clicked(bool)), this, SIGNAL(play()));
    connect(btnPause, SIGNAL(clicked(bool)), this, SIGNAL(pause()));
    connect(btnTakePicture, SIGNAL(clicked(bool)), this, SIGNAL(takePicture()));
    connect(btnComment, SIGNAL(clicked(bool)), this, SIGNAL(comment()));
}

void CameraController1::connected() {
    printf("%s() is called.", __FUNCTION__);
}

void CameraController1::disconnected() {
    printf("%s() is called.", __FUNCTION__);
    btnConnect->setEnabled(true);
}

void CameraController1::played() {
    printf("%s() is called.", __FUNCTION__);
    btnPlay->hide();
    btnPause->show();

    btnPlay->setEnabled(true);
    btnPause->setEnabled(true);
    btnDisconnect->setEnabled(true);
    btnTakePicture->setEnabled(true);
    btnComment->setEnabled(true);
}

void CameraController1::paused() {
    printf("%s() is called.", __FUNCTION__);
    btnPause->hide();
    btnPlay->show();
}

void CameraController1::stopped() {
    printf("%s() is called.", __FUNCTION__);
    btnConnect->setEnabled(true);

    btnPlay->setEnabled(false);
    btnPause->setEnabled(false);
    btnDisconnect->setEnabled(false);
    btnTakePicture->setEnabled(false);
    btnComment->setEnabled(false);
}

