#include "cameracontroller1.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QButtonGroup>
#include "common.h"
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

    btnConnect1 = new IconButton(tr("CH1"), tr(":res/icons/connect_camera_o.svg"), tr(":res/icons/connect_camera.svg"));
    btnConnect1->setFixedSize(60, 60);


    btnConnect2 = new IconButton(tr("CH2"), tr(":res/icons/connect_camera_o.svg"), tr(":res/icons/connect_camera.svg"));
    btnConnect2->setFixedSize(60, 60);
    btnConnect2->setEnabled(false);

    btnConnect3 = new IconButton(tr("CH3"), tr(":res/icons/connect_camera_o.svg"), tr(":res/icons/connect_camera.svg"));
    btnConnect3->setFixedSize(60, 60);
    btnConnect3->setEnabled(false);


    btnPlay = new QPushButton("播放");
    btnPlay->hide();
    btnPause = new QPushButton("暂停");
    btnPause->hide();
    btnDisconnect = new IconButton(tr("断开"), tr(":res/icons/disconnect_camera_o.svg"), tr(":res/icons/disconnect_camera.svg"));
    btnDisconnect->setFixedSize(60, 60);
    btnTakePicture = new IconButton(tr("拍照"), tr(":res/icons/capture_o.svg"), tr(":res/icons/capture.svg"));
    btnTakePicture->setFixedSize(60, 60);
    btnComment = new IconButton(tr("批注"), tr(":res/icons/comment_o.svg"), tr(":res/icons/comment.svg"));
    btnExit = new QPushButton("退出");
    btnExit->hide();
    btnStartRecord = new IconButton(tr("开始录制"), tr(":res/icons/start_record_o.svg"), tr(":res/icons/start_record.svg"));
    btnStopRecord = new IconButton(tr("停止录制"), tr(":res/icons/stop_record_o.svg"), tr(":res/icons/stop_record.svg"));

    btnZoomTele = new IconButton(tr("放大"), tr(":res/icons/zoom_in_o.svg"), tr(":res/icons/zoom_in.svg"));
    btnZoomWide = new IconButton(tr("缩小"), tr(":res/icons/zoom_out_o.svg"), tr(":res/icons/zoom_out.svg"));
    btnRotation = new IconButton(tr("旋转"), tr(":res/icons/zoom_out_o.svg"), tr(":res/icons/zoom_out.svg"));

    btnStopRecord->hide();
    btnStartRecord->setEnabled(false);
    btnStopRecord->setEnabled(false);
    btnZoomTele->setEnabled(false);
    btnZoomWide->setEnabled(false);
    btnPlay->setEnabled(false);
    btnPause->setEnabled(false);
    btnDisconnect->setEnabled(false);
    btnTakePicture->setEnabled(false);
    btnComment->setEnabled(false);
    btnRotation->setEnabled(false);


    /*单选菜单效果*/
    buttonGround = new QButtonGroup();
    buttonGround->setExclusive(true);
    connect(buttonGround, SIGNAL(buttonToggled(int, bool)), this, SLOT(onButtonToggled(int, bool)));
    connect(buttonGround, SIGNAL(buttonPressed(int)), this, SLOT(onButtonPressed(int)));

    //    btnConnect1->setCheckable(true);
    //    btnConnect2->setCheckable(true);
    //    btnConnect3->setCheckable(true);
    buttonGround->addButton(btnConnect1, 0);
    buttonGround->addButton(btnConnect2, 1);
    buttonGround->addButton(btnConnect3, 2);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(btnConnect1);
    hLayout->addWidget(btnConnect2);
    hLayout->addWidget(btnConnect3);
    hLayout->addSpacing(30);
    hLayout->addWidget(btnDisconnect);
    hLayout->addWidget(btnPlay);
    hLayout->addWidget(btnPause);
    hLayout->addSpacing(30);
    hLayout->addWidget(btnZoomTele);
    hLayout->addWidget(btnZoomWide);
    hLayout->addWidget(btnRotation);
    hLayout->addSpacing(30);
    hLayout->addWidget(btnStartRecord);
    hLayout->addWidget(btnStopRecord);
    hLayout->addWidget(btnTakePicture);
    hLayout->addWidget(btnComment);
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

    //    connect(btnConnect1, &QPushButton::clicked, this, [=]() {
    //        QString ip = Configure::getInstance()->getCameraIp(0);

    //        bool isOK;//QInputDialog 是否成功得到输入
    //        QString text = QInputDialog::getText(NULL,
    //                                             "设置",
    //                                             "输入摄像头IP，如: 192.168.1.100",
    //                                             QLineEdit::Normal,
    //                                             ip,
    //                                             &isOK);
    //        if(isOK) {
    //            Configure::getInstance()->setCameraIp(0, text);
    //            printf("text: %s", text.toStdString().c_str());
    //            emit signalConnect(text);
    //        }
    //    });
    connect(btnDisconnect, SIGNAL(clicked(bool)), this, SIGNAL(signalDisconnect()));

    connect(btnPlay, SIGNAL(clicked(bool)), this, SIGNAL(play()));
    connect(btnPause, SIGNAL(clicked(bool)), this, SIGNAL(pause()));
    connect(btnTakePicture, SIGNAL(clicked(bool)), this, SIGNAL(takePicture()));
    connect(btnComment, SIGNAL(clicked(bool)), this, SIGNAL(comment()));

    connect(btnStartRecord, SIGNAL(clicked(bool)), this, SIGNAL(startRecord()));
    connect(btnStopRecord, SIGNAL(clicked(bool)), this, SIGNAL(stopRecord()));

    connect(btnZoomWide, SIGNAL(clicked(bool)), this, SIGNAL(zoomWide()));
    connect(btnZoomTele, SIGNAL(clicked(bool)), this, SIGNAL(zoomTele()));

    connect(btnRotation, SIGNAL(clicked(bool)), this, SIGNAL(rotation()));
}

void CameraController1::resizeEvent(QResizeEvent *event) {
    //    QSize size = btnConnect->size();
    //    QPoint point = btnConnect->pos();
    recordIndicator->move((width() - recordIndicator->width())/2, btnConnect1->y() - recordIndicator->height());
}

void CameraController1::connected() {
    printf("%s() is called.", __FUNCTION__);
}

void CameraController1::disconnected() {
    printf("%s() is called.", __FUNCTION__);
    btnConnect1->setEnabled(true);
}

void CameraController1::played() {
    printf("%s() is called.", __FUNCTION__);
    //    btnPlay->hide();
    //    btnPause->show();
    btnConnect1->setEnabled(false);
    btnPlay->setEnabled(true);
    btnPause->setEnabled(true);
    btnDisconnect->setEnabled(true);
    btnTakePicture->setEnabled(true);
    btnComment->setEnabled(true);
    btnStartRecord->setEnabled(true);
    btnStopRecord->setEnabled(true);
    btnZoomTele->setEnabled(true);
    btnZoomWide->setEnabled(true);
    btnRotation->setEnabled(true);
}

void CameraController1::paused() {
    printf("%s() is called.", __FUNCTION__);
    btnPause->hide();
    btnPlay->show();
}

void CameraController1::stopped() {
    printf("%s() is called.", __FUNCTION__);
    btnConnect1->setEnabled(true);

    btnPlay->setEnabled(false);
    btnPause->setEnabled(false);
    btnDisconnect->setEnabled(false);
    btnTakePicture->setEnabled(false);
    btnComment->setEnabled(false);
    btnStartRecord->setEnabled(false);
    btnStopRecord->setEnabled(false);
    btnZoomTele->setEnabled(false);
    btnZoomWide->setEnabled(false);
    btnRotation->setEnabled(false);

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

void CameraController1::onButtonToggled(int index, bool checked) {
    printf("%s() index: %d checked: %d", __FUNCTION__, index, checked);
    if(!checked) {

    }
    if(checked) {
        QString ip = Configure::getInstance()->getCameraIp(index);

        bool isOK;//QInputDialog 是否成功得到输入
        QString text = QInputDialog::getText(NULL,
                                             "设置",
                                             "输入摄像头IP，如: 192.168.1.100",
                                             QLineEdit::Normal,
                                             ip,
                                             &isOK);
        if(isOK && !text.isNull() && !text.isEmpty()) {
            Configure::getInstance()->setCameraIp(index, text);
            printf("text: %s", text.toStdString().c_str());
            emit signalConnect(text);
        } else {
            emit releaseButton(index);
        }
    }
}

void CameraController1::onButtonPressed(int index) {
    printf("%s() index: %d", __FUNCTION__, index);
    buttonGround->button(index)->setCheckable(true);

    QString ip = Configure::getInstance()->getCameraIp(index);

    bool isOK;//QInputDialog 是否成功得到输入
    QString text = QInputDialog::getText(NULL,
                                         "设置",
                                         "输入摄像头IP，如: 192.168.1.100",
                                         QLineEdit::Normal,
                                         ip,
                                         &isOK);
    printf("isOK: %d text: %s", isOK, text.toStdString().c_str());
    if(isOK && !text.isNull() && !text.isEmpty()) {
        Configure::getInstance()->setCameraIp(index, text);
        printf("text: %s", text.toStdString().c_str());
        emit signalConnect(text);
    }
}
