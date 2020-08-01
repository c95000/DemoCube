#include "CameraController.h"
#include "ui_CameraController.h"
#include "common.h"

CameraController::CameraController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraController)
{
    ui->setupUi(this);

//    ui->zoom->setText("缩放");
//    ui->focus->setText("对焦");

    int iconSize = 22 * Resolution::getInstance()->scaleX();

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

    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setFixedSize(Resolution::getInstance()->scaleX() * 100, Resolution::getInstance()->scaleY() * 70);
}

CameraController::~CameraController()
{
    delete ui;
}
