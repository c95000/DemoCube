#include "ToolBar.h"
#include "ui_ToolBar.h"
#include <QLayout>
#include <QSpacerItem>
#include <QResizeEvent>
#include "SettingDialog.h"
#include "common.h"

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

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addStretch(1);
    layout->addWidget(ui->btnInsert, 0, Qt::AlignCenter);
    layout->addWidget(ui->btnComment, 0, Qt::AlignHCenter);
    layout->addWidget(ui->btnTakePicture, 0, Qt::AlignHCenter);
    layout->addWidget(ui->btnTakeVideo, 0, Qt::AlignHCenter);
    layout->addWidget(ui->btnPlayPause, 0, Qt::AlignHCenter);
    layout->addWidget(ui->btnSetting, 0, Qt::AlignHCenter);
//    layout->addWidget(ui->btnSetting, 0, Qt::AlignHCenter | Qt::AlignBottom);
    layout->addStretch(1);
    setLayout(layout);

    connect(ui->btnSetting->pushButton(), &QPushButton::clicked, this, &ToolBar::onSettingButtonClicked);
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

void ToolBar::resizeEvent(QResizeEvent *event) {

    int ax = event->size().width() - ui->cameraController->width() - 5;
    int ay = (event->size().height() - ui->cameraController->height()) / 2;

    ui->cameraController->move(ax, ay);
}


void ToolBar::onSettingButtonClicked() {
    printf("onSettingButtonClicked");
    SettingDialog *dlg=new SettingDialog(this);

    int ret = dlg->exec();
    if(ret==QDialog::Accepted) {
        printf("!ret:%d", ret);
    } else {
        printf("ret:%d", ret);
    }
    delete dlg;

//        Qt::WindowFlags flags=dlgTableSize->windowFlags();
//        dlgTableSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
//        dlgTableSize->setRowColumn(theModel->rowCount(),theModel->columnCount ());
//        int ret=dlgTableSize->exec () ;// 以模态方式显示对话框
//        if (ret==QDialog::Accepted)
//        { //OK按钮被按下，获取对话框上的输入，设置行数和列数
//            int cols=dlgTableSize->columnCount();
//            theModel->setColumnCount(cols);
//            int rows=dlgTableSize->rowCount();
//            theModel->setRowCount(rows);
//        }
//        delete dlgTableSize;
}

