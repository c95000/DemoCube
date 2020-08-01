#include "CameraManager.h"
#include "ui_CameraManager.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include "common.h"

CameraManager::CameraManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraManager)
{
    ui->setupUi(this);

    ui->camera1->setText(QString("视频1"));
    ui->camera1->imageButton()->setImages(QPixmap(":/images/res/images/camera_setting.png"), 30, 30);

    ui->camera2->setText(QString("视频2"));
    ui->camera2->imageButton()->setImages(QPixmap(":/images/res/images/camera_setting.png"), 30, 30);

    ui->camera3->setText(QString("视频3"));
    ui->camera3->imageButton()->setImages(QPixmap(":/images/res/images/camera_setting.png"), 30, 30);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(ui->camera1, 0, Qt::AlignHCenter);
    layout->addWidget(ui->camera2, 0, Qt::AlignHCenter);
    layout->addWidget(ui->camera3, 0, Qt::AlignHCenter);
    layout->addStretch(1);
    setLayout(layout);

    connect(ui->camera1->button(), &QPushButton::clicked, this, &CameraManager::onVideoSetting1_Clicked);
    connect(ui->camera2->button(), &QPushButton::clicked, this, &CameraManager::onVideoSetting2_Clicked);
    connect(ui->camera3->button(), &QPushButton::clicked, this, &CameraManager::onVideoSetting3_Clicked);
}

CameraManager::~CameraManager()
{
    delete ui;
}

void CameraManager::onVideoSetting1_Clicked() {
    setCameraUrl(0);
}
void CameraManager::onVideoSetting2_Clicked() {
    setCameraUrl(1);
}
void CameraManager::onVideoSetting3_Clicked() {
    setCameraUrl(2);
}

void CameraManager::setCameraUrl(int index) {
    printf("setCameraUrl:%d", index);
    bool bOk = false;
//    QString("摄像头(%1)").arg(index);
    QString sRtsp = QInputDialog::getText(this, QString("视频%1").arg(index + 1),
        tr("请设置IP地址:"), QLineEdit::Normal,
        "192.168.1.225", &bOk);
    // rtsp://192.168.1.225/
    sRtsp = "rtsp://" + sRtsp + "/";
    printf("rtsp:%s", sRtsp.toStdString().c_str());
}
