#include "ToolBar.h"
#include "ui_ToolBar.h"

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);
    ui->btnWhiteBoard->setText(QString("白板"));
    ui->btnWhiteBoard->setImages(QPixmap(":/images/res/images/whiteboard.png"));
    ui->btnInsert->setText(QString("插入"));
    ui->btnInsert->setImages(QPixmap(":/images/res/images/insert.png"));
    ui->btnComment->setText(QString("批注"));
    ui->btnComment->setImages(QPixmap(":/images/res/images/comment.png"));
    ui->btnCapturePicture->setText(QString("拍照"));
    ui->btnCapturePicture->setImages(QPixmap(":/images/res/images/takepicture.png"));
}

ToolBar::~ToolBar()
{
    delete ui;
}

const QPushButton *ToolBar::whiteBoardButton() {
    return ui->btnWhiteBoard->pushButton();
}

const QPushButton *ToolBar::insertButton() {
return ui->btnInsert->pushButton();
}

const QPushButton *ToolBar::commentButton() {
return ui->btnComment->pushButton();
}

const QPushButton *ToolBar::capturePictureButton() {
return ui->btnCapturePicture->pushButton();
}
