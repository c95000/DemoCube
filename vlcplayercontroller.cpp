#include "vlcplayercontroller.h"
#include "ui_vlcplayercontroller.h"
#include <QHBoxLayout>

VlcPlayerController::VlcPlayerController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VlcPlayerController)
{
    ui->setupUi(this);

    btnPlay = new QPushButton("播放");
    btnPlay->hide();
    btnPause = new QPushButton("暂停");
    btnStop = new QPushButton("停止");
    btnTakePicture = new QPushButton("拍照");
    btnComment = new QPushButton("批注");
    btnExit = new QPushButton("退出");

    connect(btnPlay, SIGNAL(clicked(bool)), this, SIGNAL(play()));
    connect(btnPause, SIGNAL(clicked(bool)), this, SIGNAL(pause()));
    connect(btnStop, SIGNAL(clicked(bool)), this, SIGNAL(stop()));
    connect(btnTakePicture, SIGNAL(clicked(bool)), this, SIGNAL(takePicture()));
    connect(btnComment, SIGNAL(clicked(bool)), this, SIGNAL(comment()));
    connect(btnExit, SIGNAL(clicked(bool)), this, SIGNAL(close()));


    connect(btnPlay, SIGNAL(clicked(bool)), this, SLOT(onPlay()));
    connect(btnPause, SIGNAL(clicked(bool)), this, SLOT(onPause()));

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(btnPlay);
    hLayout->addWidget(btnPause);
    hLayout->addWidget(btnStop);
    hLayout->addWidget(btnTakePicture);
    hLayout->addWidget(btnComment);
    hLayout->addStretch();

    setLayout(hLayout);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setMinimumHeight(50);
    setMaximumHeight(50);
}

VlcPlayerController::~VlcPlayerController()
{
    delete ui;
}


void VlcPlayerController::onPlay() {
    btnPlay->hide();
    btnPause->show();
}

void VlcPlayerController::onPause() {
    btnPause->hide();
    btnPlay->show();
}
