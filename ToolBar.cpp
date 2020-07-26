#include "ToolBar.h"
#include "ui_ToolBar.h"

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);

    ui->btnInsert->setText(QString("插入"));
    ui->btnInsert->imageButton()->setImages(":/images/res/images/insert.png", 50, 50);

    ui->btnComment->setText(QString("批注"));
    ui->btnComment->imageButton()->setImages(QPixmap(":/images/res/images/comment.png"), 50, 50);

    ui->btnTakePicture->setText(QString("拍照"));
    ui->btnTakePicture->imageButton()->setImages(QPixmap(":/images/res/images/takepicture.png"), 50, 50);

    ui->btnTakeVideo->setText(QString("录像"));
    ui->btnTakeVideo->imageButton()->setImages(QPixmap(":/images/res/images/takevideo.png"), 50, 50);

    ui->btnPlayPause->setText(QString("播放"));
    ui->btnPlayPause->imageButton()->setImages(QPixmap(":/images/res/images/play.png"), 50, 50);

    ui->btnSetting->setText(QString("设置"));
    ui->btnSetting->imageButton()->setImages(QPixmap(":/images/res/images/setting.png"), 50, 50);
}

ToolBar::~ToolBar()
{
    delete ui;
}


const QPushButton *ToolBar::insertButton() {
    return ui->btnInsert->pushButton();
}

const QPushButton *ToolBar::commentButton() {
    return ui->btnComment->pushButton();
}


const QPushButton *ToolBar::takePictureButton() {
    return ui->btnTakePicture->pushButton();
}

const QPushButton *ToolBar::takeVideoButton() {
    return ui->btnTakeVideo->pushButton();
}

const QPushButton *ToolBar::playPauseButton() {
    return ui->btnComment->pushButton();
}

const QPushButton *ToolBar::settingButton() {
    return ui->btnComment->pushButton();
}
