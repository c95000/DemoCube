#include "MediaController.h"
#include "ui_MediaController.h"

MediaController::MediaController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaController)
{
    ui->setupUi(this);
//    setStyleSheet ("background-color: rgb(255, 255, 0);");

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::yellow); //设置背景黑色
    setAutoFillBackground(true);
    setPalette(pal);
}

MediaController::~MediaController()
{
    delete ui;
}

const QLabel * MediaController::timeLable() {
    return ui->time;
}

const QPushButton *MediaController::playPauseButton() {
    return ui->playPause;
}

const QPushButton *MediaController::stopButton() {
    return ui->stop;
}
