#include "cameracontroller1.h"
#include <QFileDialog>
#include <QInputDialog>

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
    btnPause->hide();
    btnDisconnect = new QPushButton("断开");
    btnTakePicture = new QPushButton("拍照");
    btnComment = new QPushButton("批注");
    btnComment->hide();
    btnExit = new QPushButton("退出");
    btnExit->hide();
    btnStartRecord = new QPushButton("开始录制");
    btnStopRecord = new QPushButton("结束录制");
    btnStartRecord->setEnabled(false);
    btnStopRecord->setEnabled(false);
    btnStopRecord->hide();
    btnZoomin = new QPushButton("放大");
    btnZoomout = new QPushButton("缩小");

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
    hLayout->addWidget(btnStartRecord);
    hLayout->addWidget(btnStopRecord);
    hLayout->addWidget(btnZoomin);
    hLayout->addWidget(btnZoomout);
    hLayout->addStretch();


    recordIndicator = new RecordIndicator(this);
    recordIndicator->resize(130, 30);
//    QHBoxLayout *recordLayout = new QHBoxLayout();
//    QSpacerItem *leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding);
//    recordLayout->addSpacerItem(leftSpacer);
//    recordLayout->addStretch();
//    recordLayout->addWidget(recordIndicator);
//    recordLayout->addStretch();

//    QVBoxLayout *vLayout = new QVBoxLayout();
//    vLayout->addLayout(recordLayout);
//    vLayout->addLayout(hLayout);


    setLayout(hLayout);

    connect(btnConnect, &QPushButton::clicked, this, [=]() {
        sourceUrl = "rtsp://192.168.1.225/";

        QString ip = Configure::getInstance()->getCameraIp(0);

        bool isOK;//QInputDialog 是否成功得到输入
        QString text = QInputDialog::getText(NULL,
                                             "设置",
                                             "输入摄像头IP，如: 192.168.1.100",
                                             QLineEdit::Normal,
                                             ip,
                                             &isOK);
        if(isOK) {
            Configure::getInstance()->setCameraIp(0, text);
            printf("text: %s", text.toStdString().c_str());
            emit signalConnect(text);
        }
        //C:\Users\201708\Pictures\eb3aa50943c201336de9fa1c23b5a6c5-480p.mp4

    });
    connect(btnDisconnect, SIGNAL(clicked(bool)), this, SIGNAL(signalDisconnect()));

    connect(btnPlay, SIGNAL(clicked(bool)), this, SIGNAL(play()));
    connect(btnPause, SIGNAL(clicked(bool)), this, SIGNAL(pause()));
    connect(btnTakePicture, SIGNAL(clicked(bool)), this, SIGNAL(takePicture()));
    connect(btnComment, SIGNAL(clicked(bool)), this, SIGNAL(comment()));

    connect(btnStartRecord, SIGNAL(clicked(bool)), this, SIGNAL(startRecord()));
    connect(btnStopRecord, SIGNAL(clicked(bool)), this, SIGNAL(stopRecord()));

    connect(btnZoomin, SIGNAL(clicked(bool)), this, SIGNAL(zoomin()));
    connect(btnZoomout, SIGNAL(clicked(bool)), this, SIGNAL(zoomout()));
}

void CameraController1::resizeEvent(QResizeEvent *event) {
//    QSize size = btnConnect->size();
//    QPoint point = btnConnect->pos();
    recordIndicator->move((width() - recordIndicator->width())/2, btnConnect->y() - recordIndicator->height());
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
//    btnPlay->hide();
//    btnPause->show();

    btnPlay->setEnabled(true);
    btnPause->setEnabled(true);
    btnDisconnect->setEnabled(true);
    btnTakePicture->setEnabled(true);
    btnComment->setEnabled(true);
    btnStartRecord->setEnabled(true);
    btnStopRecord->setEnabled(true);
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
    btnStartRecord->setEnabled(false);
    btnStopRecord->setEnabled(false);

    stopRecorded();
}


void CameraController1::startRecorded() {
    recordIndicator->start();
    btnStartRecord->hide();
    btnStopRecord->show();
}

void CameraController1::stopRecorded() {
    recordIndicator->stop();
    btnStartRecord->show();
    btnStopRecord->hide();
}
