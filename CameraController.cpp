#include "CameraController.h"
#include "ui_CameraController.h"

CameraController::CameraController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraController)
{
    ui->setupUi(this);

    ui->zoom->setText("缩放");
    ui->focus->setText("对焦");
}

CameraController::~CameraController()
{
    delete ui;
}
