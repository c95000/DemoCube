#include "CameraController.h"
#include "ui_CameraController.h"
#include "common.h"
#include "Resolution.h"

CameraController::CameraController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraController)
{
    ui->setupUi(this);

//    ui->zoom->setText("缩放");
//    ui->focus->setText("对焦");

    int iconSize = 30 * Resolution::getInstance()->scaleX();

    ui->zoomdown->setImages(QPixmap(":/images/res/images/sub1.png"), iconSize, iconSize);
    ui->zoomup->setImages(QPixmap(":/images/res/images/add1.png"), iconSize, iconSize);
    ui->focusdown->setImages(QPixmap(":/images/res/images/sub1.png"), iconSize, iconSize);
    ui->focusup->setImages(QPixmap(":/images/res/images/add1.png"), iconSize, iconSize);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(180, 180, 180)); //设置背景黑色

    ui->zoomContainer->setAutoFillBackground(true);
    ui->zoomContainer->setPalette(pal);

    ui->focusContainer->setAutoFillBackground(true);
    ui->focusContainer->setPalette(pal);

    ui->focusContainer->hide();

    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setFixedSize(Resolution::getInstance()->scaleX() * 120, Resolution::getInstance()->scaleY() * 40);

    connect(ui->zoomup, &QPushButton::clicked, this, &CameraController::onZoomTeleClicked);
    connect(ui->zoomdown, &QPushButton::clicked, this, &CameraController::onZoomWideClicked);
}

CameraController::~CameraController()
{
    delete ui;
}

void CameraController::onZoomTeleClicked() {
    printf("%s", __FUNCTION__);
    emit zoomTele();
}

void CameraController::onZoomWideClicked() {
    printf("%s", __FUNCTION__);
    emit zoomWide();
}
