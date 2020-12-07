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
    btnOpen = new IconButton(tr("打开"), tr(":res/icons/open_file_o.svg"), tr(":res/icons/open_file.svg"));
    btnPlay = new IconButton(tr("播放"), tr(":res/icons/play_o.svg"), tr(":res/icons/play.svg"));

    btnPause = new IconButton(tr("暂停"), tr(":res/icons/pause_o.svg"), tr(":res/icons/pause.svg"));
    btnStop = new IconButton(tr("停止"), tr(":res/icons/stop_o.svg"), tr(":res/icons/stop.svg"));
    btnTakePicture = new IconButton(tr("拍照"), tr(":res/icons/capture_o.svg"), tr(":res/icons/capture.svg"));
    btnComment = new IconButton(tr("批注"), tr(":res/icons/comment_o.svg"), tr(":res/icons/comment.svg"));
    btnExit = new QPushButton("退出");

    btnPlay->hide();
    btnExit->hide();

    btnPlay->setEnabled(false);
    btnPause->setEnabled(false);;
    btnStop->setEnabled(false);;
    btnTakePicture->setEnabled(false);;
    btnComment->setEnabled(false);

    connect(btnPlay, SIGNAL(clicked(bool)), this, SIGNAL(play()));
    connect(btnPause, SIGNAL(clicked(bool)), this, SIGNAL(pause()));
    connect(btnStop, SIGNAL(clicked(bool)), this, SIGNAL(stop()));
    connect(btnComment, SIGNAL(clicked(bool)), this, SIGNAL(comment()));
    connect(btnTakePicture, SIGNAL(clicked(bool)), this, SIGNAL(takePicture()));
    connect(btnExit, SIGNAL(clicked(bool)), this, SIGNAL(close()));

    connect(btnOpen, SIGNAL(clicked(bool)), this, SLOT(onOpen()));
//    connect(btnPlay, SIGNAL(clicked(bool)), this, SLOT(onPlay()));
//    connect(btnPause, SIGNAL(clicked(bool)), this, SLOT(onPause()));

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(btnOpen);
    hLayout->addSpacing(40);
    hLayout->addWidget(btnPlay);
    hLayout->addWidget(btnPause);
    hLayout->addWidget(btnStop);
    hLayout->addSpacing(40);
    hLayout->addWidget(btnTakePicture);
    hLayout->addWidget(btnComment);
    hLayout->addStretch();

    setLayout(hLayout);
//    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//    setMinimumHeight(50);
//    setMaximumHeight(50);


    progressBar = new ProgressBar(this);
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
    printf("stopped");
}

void VlcPlayerController::updateProgress(int current, int total) {
//    printf("VlcPlayerController %s current: %d total: %d", __FUNCTION__, current, total);
    progressBar->setValue(current, total);
}

void VlcPlayerController::resizeEvent(QResizeEvent *event) {
    progressBar->move(btnOpen->x(), btnOpen->y() - progressBar->height());

    int w = btnComment->geometry().right() - btnOpen->x();
    progressBar->setFixedWidth(w);
}
