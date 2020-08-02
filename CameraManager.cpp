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

    urlList = new QList<QString>();
    urlList->append(QString());
    urlList->append(QString());
    urlList->append(QString());

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

    connect(ui->camera1->button(), &QPushButton::clicked, this, &CameraManager::onSettingClicked);
    connect(ui->camera2->button(), &QPushButton::clicked, this, &CameraManager::onSettingClicked);
    connect(ui->camera3->button(), &QPushButton::clicked, this, &CameraManager::onSettingClicked);

    connect(ui->camera1, &HTitleButton::doubleClicked, this, &CameraManager::onDoubleClicked);
    connect(ui->camera2, &HTitleButton::doubleClicked, this, &CameraManager::onDoubleClicked);
    connect(ui->camera3, &HTitleButton::doubleClicked, this, &CameraManager::onDoubleClicked);

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
    delete urlList;
}

void CameraManager::resizeEvent(QResizeEvent *event) {
//    int ax = event->size().width() - ui->cameraController->width() - 5;
//    int ay = (event->size().height() - ui->cameraController->height()) / 2;
//    printf("old size: %d x %d", event->oldSize().width(), event->oldSize().height());
//    printf("new size: %d x %d", event->size().width(), event->size().height());
}

void CameraManager::onSettingClicked() {
    QPushButton *obj = qobject_cast<QPushButton*>(sender());
    int index = -1;
    if(obj == ui->camera1->button()) {
        index = 0;
    } else if(obj == ui->camera2->button()) {
        index = 1;
    } else if(obj == ui->camera3->button()) {
        index = 2;
    }

    setCameraUrl(index);
}

void CameraManager::onDoubleClicked() {
    HTitleButton *obj = qobject_cast<HTitleButton*>(sender());
    printf("onDoubleClicked: %p", obj);
    printf("videoes: %p %p %p", ui->camera1, ui->camera2, ui->camera3);
    int index = -1;
    if(obj == ui->camera1) {
        index = 0;
    } else if(obj == ui->camera2) {
        index = 1;
    } else if(obj == ui->camera3) {
        index = 2;
    }
    if(index >= 0 && index < urlList->size()) {
         QString url = urlList->at(index);
         emit selectedRtsp(url);
    }
}

void CameraManager::setCameraUrl(int index) {
    printf("setCameraUrl:%d", index);
    bool bOk = false;
//    QString("摄像头(%1)").arg(index);
    QString sRtsp = QInputDialog::getText(this, QString("视频%1").arg(index + 1),
        tr("请设置IP地址:"), QLineEdit::Normal,
        "192.168.1.225", &bOk);
    // rtsp://192.168.1.225/
    if(!sRtsp.isEmpty()) {
//        sRtsp = "rtsp://" + sRtsp + "/";
        printf("[%d] rtsp:%s", index, sRtsp.toStdString().c_str());
        urlList->replace(index, sRtsp);
    }
    for(int i = 0; i < urlList->size(); i++) {
        printf("%d : %s", i, urlList->at(i).toStdString().c_str());
    }
}
