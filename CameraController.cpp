#include "CameraController.h"
#include "ui_CameraController.h"

CameraController::CameraController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraController)
{
    ui->setupUi(this);

//    ui->zoom->setText("缩放");
//    ui->focus->setText("对焦");

    ui->zoomdown->setImages(QPixmap(":/images/res/images/sub1.png"), 20, 20);
    ui->zoomup->setImages(QPixmap(":/images/res/images/add1.png"), 20, 20);
    ui->focusdown->setImages(QPixmap(":/images/res/images/sub1.png"), 20, 20);
    ui->focusup->setImages(QPixmap(":/images/res/images/add1.png"), 20, 20);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(180, 180, 180)); //设置背景黑色

    ui->zoomContainer->setAutoFillBackground(true);
    ui->zoomContainer->setPalette(pal);

    ui->focusContainer->setAutoFillBackground(true);
    ui->focusContainer->setPalette(pal);

    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setFixedSize(80, 50);

}

CameraController::~CameraController()
{
    delete ui;
}
