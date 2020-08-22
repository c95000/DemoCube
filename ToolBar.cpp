#include "ToolBar.h"
#include "ui_ToolBar.h"
#include <QLayout>
#include <QSpacerItem>
#include <QResizeEvent>
#include "SettingDialog.h"
#include "Configure.h"
#include "common.h"

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);

    int iconSize = Resolution::getInstance()->scaleX() * 50;

    ui->btnInsert->setText(QString("回放"));
    ui->btnInsert->imageButton()->setImages(":/images/res/images/insert.png", iconSize, iconSize);

    ui->btnComment->setText(QString("批注"));
    ui->btnComment->imageButton()->setImages(QPixmap(":/images/res/images/comment.png"), iconSize, iconSize);

    ui->btnTakePicture->setText(QString("拍照"));
    ui->btnTakePicture->imageButton()->setImages(QPixmap(":/images/res/images/takepicture.png"), iconSize, iconSize);

    ui->btnTakeVideo->setText(QString("录像"));
    ui->btnTakeVideo->imageButton()->setImages(QPixmap(":/images/res/images/takevideo.png"), iconSize, iconSize);

    ui->btnPlayPause->setText(QString("播放"));
    ui->btnPlayPause->imageButton()->setImages(QPixmap(":/images/res/images/play.png"), iconSize, iconSize);

    ui->btnSetting->setText(QString("设置"));
    ui->btnSetting->imageButton()->setImages(QPixmap(":/images/res/images/setting.png"), iconSize, iconSize);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addStretch(3);
    if(!Configure::getInstance()->isAllowCommenting()) {
        ui->btnComment->hide();
    }
    layout->addWidget(ui->btnInsert, 1, Qt::AlignHCenter);
    layout->addWidget(ui->btnComment, 1, Qt::AlignHCenter);
    layout->addWidget(ui->btnTakePicture, 1, Qt::AlignHCenter);
    layout->addWidget(ui->btnTakeVideo, 1, Qt::AlignHCenter);
    layout->addWidget(ui->btnPlayPause, 1, Qt::AlignHCenter);
    layout->addWidget(ui->btnSetting, 1, Qt::AlignHCenter);
    layout->addStretch(3);
    setLayout(layout);

//    int default_width = getDesktopWidth() / 12;
//    int default_height = getDesktopHeight() / 12;

//    printf("parent size: %d x %d", parentWidget()->size().width(), parentWidget()->size().height());
//    printf("init size: %d x %d", size().width(), size().height());
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setFixedHeight(Resolution::getInstance()->scaleY() * 120);

    connect(ui->btnSetting->pushButton(), &QPushButton::clicked, this, &ToolBar::onSettingButtonClicked);
    ui->cameraController->hide();
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
    return ui->btnPlayPause->pushButton();
}

TitleButton *ToolBar::playPause() {
    return ui->btnPlayPause;
}

const QPushButton *ToolBar::settingButton() {
    return ui->btnSetting->pushButton();
}

void ToolBar::resizeEvent(QResizeEvent *event) {

    int ax = event->size().width() - ui->cameraController->width() - 15;
    int ay = (event->size().height() - ui->cameraController->height()) / 2 - 5;

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

