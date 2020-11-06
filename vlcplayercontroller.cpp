#include "vlcplayercontroller.h"
#include "ui_vlcplayercontroller.h"
#include <QHBoxLayout>

VlcPlayerController::VlcPlayerController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VlcPlayerController)
{
    ui->setupUi(this);

    ui->setupUi(this);

    btnPlay = new QPushButton("播放");
    btnPause = new QPushButton("暂停");
    btnStop = new QPushButton("停止");
    btnExit = new QPushButton("退出");

    connect(btnPlay, SIGNAL(clicked(bool)), this, SIGNAL(play()));
    connect(btnPause, SIGNAL(clicked(bool)), this, SIGNAL(pause()));
    connect(btnStop, SIGNAL(clicked(bool)), this, SIGNAL(stop()));
    connect(btnExit, SIGNAL(clicked(bool)), this, SIGNAL(exit()));

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(btnPlay);
    hLayout->addWidget(btnPause);
    hLayout->addWidget(btnStop);
    hLayout->addWidget(btnExit);
    hLayout->addStretch();

    setLayout(hLayout);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

VlcPlayerController::~VlcPlayerController()
{
    delete ui;
}
