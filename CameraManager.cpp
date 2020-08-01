#include "CameraManager.h"
#include "ui_CameraManager.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QResizeEvent>
#include "common.h"

CameraManager::CameraManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraManager)
{
    ui->setupUi(this);

//    int initWidth = parent->size().width();
//    int initHeight = parent->size().height();
//    printf("CameraManager: %d x %d", initWidth, initHeight);

    int iconSize = Resolution::getInstance()->scaleX() * 30;

    ui->camera1->setText(QString("视频1"));
    ui->camera1->imageButton()->setImages(QPixmap(":/images/res/images/camera_setting.png"), iconSize, iconSize);

    ui->camera2->setText(QString("视频2"));
    ui->camera2->imageButton()->setImages(QPixmap(":/images/res/images/camera_setting.png"), iconSize, iconSize);

    ui->camera3->setText(QString("视频3"));
    ui->camera3->imageButton()->setImages(QPixmap(":/images/res/images/camera_setting.png"), iconSize, iconSize);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(ui->camera1, 0, Qt::AlignHCenter);
    layout->addWidget(ui->camera2, 0, Qt::AlignHCenter);
    layout->addWidget(ui->camera3, 0, Qt::AlignHCenter);
    layout->addStretch(1);
    setLayout(layout);

    connect(ui->camera1->button(), &QPushButton::clicked, this, &CameraManager::onVideoSetting1_Clicked);
    connect(ui->camera2->button(), &QPushButton::clicked, this, &CameraManager::onVideoSetting2_Clicked);
    connect(ui->camera3->button(), &QPushButton::clicked, this, &CameraManager::onVideoSetting3_Clicked);

//    int default_width = getDesktopWidth() / 12;
//    int default_height = getDesktopHeight() / 12;

//    printf("parent size: %d x %d", parentWidget()->size().width(), parentWidget()->size().height());
//    printf("init size: %d x %d", size().width(), size().height());
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    setFixedWidth(Resolution::getInstance()->scaleX() * 140);
}

CameraManager::~CameraManager()
{
    delete ui;
}

void CameraManager::resizeEvent(QResizeEvent *event) {
//    int ax = event->size().width() - ui->cameraController->width() - 5;
//    int ay = (event->size().height() - ui->cameraController->height()) / 2;
//    printf("old size: %d x %d", event->oldSize().width(), event->oldSize().height());
//    printf("new size: %d x %d", event->size().width(), event->size().height());
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
