#include "ToolBar.h"
#include "ui_ToolBar.h"

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);
    ui->btnWhiteBoard->setText(QString("白板"));
    ui->btnInsert->setText(QString("插入"));
    ui->btnComment->setText(QString("批注"));
    ui->btnCapturePicture->setText(QString("拍照"));
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
