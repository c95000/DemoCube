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
    btnExit = new QPushButton("退出");
    btnExit->hide();
    btnStartRecord = new QPushButton("开始录制");
    btnStopRecord = new QPushButton("结束录制");
    btnStartRecord->setEnabled(false);
    btnStopRecord->setEnabled(false);
    btnStopRecord->hide();
    btnZoomTele = new QPushButton("放大");
    btnZoomWide = new QPushButton("缩小");
    btnZoomTele->setEnabled(false);
    btnZoomWide->setEnabled(false);


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
    hLayout->addWidget(btnZoomTele);
    hLayout->addWidget(btnZoomWide);
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
//        sourceUrl = "C:\\nginx-1.16.0\\html\\mfc\\20s_video.mp4";

//        printf("on_btnLocal_clicked");
//        QString videoPath = Configure::getInstance()->getVideopath();
//        QString filename = QFileDialog::getOpenFileName(this,tr("action"),videoPath,"",0);
//        if(filename.isEmpty()) {
//            return;
//        }

//        printf("filename: %s", filename.toStdString().c_str());
//        filename = filename.replace("/", "\\");
//        sourceUrl = filename;

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
    });
    connect(btnDisconnect, SIGNAL(clicked(bool)), this, SIGNAL(signalDisconnect()));

    connect(btnPlay, SIGNAL(clicked(bool)), this, SIGNAL(play()));
    connect(btnPause, SIGNAL(clicked(bool)), this, SIGNAL(pause()));
    connect(btnTakePicture, SIGNAL(clicked(bool)), this, SIGNAL(takePicture()));
    connect(btnComment, SIGNAL(clicked(bool)), this, SIGNAL(comment()));

    connect(btnStartRecord, SIGNAL(clicked(bool)), this, SIGNAL(startRecord()));
    connect(btnStopRecord, SIGNAL(clicked(bool)), this, SIGNAL(stopRecord()));

    connect(btnZoomWide, SIGNAL(clicked(bool)), this, SIGNAL(zoomWide()));
    connect(btnZoomTele, SIGNAL(clicked(bool)), this, SIGNAL(zoomTele()));
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
    btnConnect->setEnabled(false);
    btnPlay->setEnabled(true);
    btnPause->setEnabled(true);
    btnDisconnect->setEnabled(true);
    btnTakePicture->setEnabled(true);
    btnComment->setEnabled(true);
    btnStartRecord->setEnabled(true);
    btnStopRecord->setEnabled(true);
    btnZoomTele->setEnabled(true);
    btnZoomWide->setEnabled(true);
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
    btnZoomTele->setEnabled(false);
    btnZoomWide->setEnabled(false);

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
