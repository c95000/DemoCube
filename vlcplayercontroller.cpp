#include "vlcplayercontroller.h"
#include "ui_vlcplayercontroller.h"
#include <QHBoxLayout>
#include "Configure.h"
#include <QFileDialog>
#include "common.h"

VlcPlayerController::VlcPlayerController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VlcPlayerController)
{
    ui->setupUi(this);
    btnOpen = new QPushButton("打开文件");
    btnPlay = new QPushButton("播放");
    btnPlay->hide();
    btnPause = new QPushButton("暂停");
    btnStop = new QPushButton("停止");
    btnTakePicture = new QPushButton("拍照");
    btnComment = new QPushButton("批注");
    btnExit = new QPushButton("退出");
    btnExit->hide();

    btnPlay->setEnabled(false);
    btnPause->setEnabled(false);;
    btnStop->setEnabled(false);;
    btnTakePicture->setEnabled(false);;
    btnComment->setEnabled(false);

    connect(btnPlay, SIGNAL(clicked(bool)), this, SIGNAL(play()));
    connect(btnPause, SIGNAL(clicked(bool)), this, SIGNAL(pause()));
    connect(btnStop, SIGNAL(clicked(bool)), this, SIGNAL(stop()));
    connect(btnTakePicture, SIGNAL(clicked(bool)), this, SIGNAL(takePicture()));
    connect(btnComment, SIGNAL(clicked(bool)), this, SIGNAL(comment()));
    connect(btnExit, SIGNAL(clicked(bool)), this, SIGNAL(close()));

    connect(btnOpen, SIGNAL(clicked(bool)), this, SLOT(onOpen()));
//    connect(btnPlay, SIGNAL(clicked(bool)), this, SLOT(onPlay()));
//    connect(btnPause, SIGNAL(clicked(bool)), this, SLOT(onPause()));

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(btnOpen);
    hLayout->addWidget(btnPlay);
    hLayout->addWidget(btnPause);
    hLayout->addWidget(btnStop);
    hLayout->addWidget(btnTakePicture);
    hLayout->addWidget(btnComment);
    hLayout->addStretch();

    setLayout(hLayout);
//    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//    setMinimumHeight(50);
//    setMaximumHeight(50);
}

VlcPlayerController::~VlcPlayerController()
{
    delete ui;
}

void VlcPlayerController::onOpen() {
    printf("on_btnLocal_clicked");
    QString videoPath = Configure::getInstance()->getVideopath();
    QString filename = QFileDialog::getOpenFileName(this,tr("action"),videoPath,"",0);
    if(filename.isEmpty()) {
        return;
    }

    printf("filename: %s", filename.toStdString().c_str());
    emit play(filename);
//    filename.replace("/", "\\");
//    replaseWidget(vlcPlayer);
//    vlcPlayer->play(filename);
}

void VlcPlayerController::onPlay() {
    btnPlay->hide();
    btnPause->show();
}

void VlcPlayerController::onPause() {
    btnPause->hide();
    btnPlay->show();
}


void VlcPlayerController::played() {
    btnPlay->hide();
    btnPause->show();

    btnPlay->setEnabled(true);
    btnPause->setEnabled(true);;
    btnStop->setEnabled(true);;
    btnTakePicture->setEnabled(true);;
    btnComment->setEnabled(true);
}

void VlcPlayerController::paused() {
    btnPause->hide();
    btnPlay->show();
}
void VlcPlayerController::stopped() {

}
