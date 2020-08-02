#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTime>
#include <QScreen>
#include <QLabel>
#include "Util.h"
#include <iostream>
#include <QScreen>
#include <QDesktopWidget>
#include "common.h"
#include "Resolution.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QPalette pal(palette());
//    pal.setColor(QPalette::Background, QColor(135,206,235)); //设置背景黑色
//    setAutoFillBackground(true);
//    setPalette(pal);

//    QScreen *screen=QGuiApplication::primaryScreen ();
//    QRect mm = screen->availableGeometry() ;
//    int screen_width = mm.width();
//    int screen_height = mm.height();
//    printf("screen %d x %d", screen_width, screen_height);

//    int desktop_width = QApplication::desktop()->width();
//    int desktop_height = QApplication::desktop()->height();
//    printf("desktop %d x %d", desktop_width, desktop_height);


//    printf("desktop %f x %f", Resolution::scaleX(), Resolution::scaleY());

//    int default_width = 1280;
//    int default_height = 720;
//    if(desktop_width > 0 && desktop_height > 0) {
//        default_width = desktop_width * 2 / 3;
//        default_height = desktop_height * 2 / 3;
//    }
    int default_width = 1280 * Resolution::getInstance()->scaleX();
    int default_height = 720 * Resolution::getInstance()->scaleY();
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumSize(QSize(default_width, default_height));

//    setStyleSheet("color:red;");

//    QPalette pe;
//    pe.setColor(QPalette::WindowText,Qt::white);
//    setPalette(pe);

    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(":/images/res/images/background.png");
    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);


    connect(ui->toolBar->insertButton(), &QPushButton::clicked, this, &MainWindow::on_btnPlayLocal_clicked);
    connect(ui->toolBar->commentButton(), &QPushButton::clicked, this, &MainWindow::on_btnComment_clicked);
    connect(ui->toolBar->takePictureButton(), &QPushButton::clicked, this, &MainWindow::on_takePicture);
    connect(ui->toolBar->playPauseButton(), &QPushButton::clicked, this, &MainWindow::on_btnPlayPause_clicked);

//    connect(ui->toolBar->capturePictureButton(), &QPushButton::clicked, this, &MainWindow::on_btnDevice_clicked);

//    connect(ui->mediaController->playPauseButton(), &QPushButton::clicked, this, &MainWindow::on_btnPlayPause_clicked);
//    connect(ui->mediaController->stopButton(), &QPushButton::clicked, this, &MainWindow::on_btnStop_clicked);

//    QHBoxLayout* layout = new QHBoxLayout(this);
//    layout->addStretch(1);
//    layout->addWidget(ui->toolBar, 0, Qt::AlignHCenter);
//    layout->addStretch(1);
//    ui->footer->setLayout(layout);


//    myPaint = new MyPaint(this);
//    myPaint->setParent(nullptr);

//    myNotation = new MyPaint(this);
//    myNotation->setParent(nullptr);
    //ui->gridLayout->addWidget(myPaint, 0, 0);

    timerClock = new QTimer();
    connect(timerClock,  SIGNAL(timeout()), this, SLOT(on_timeout()));
    timerClock->setInterval(1000);
    vlcWrapper = new VlcWrapper();

    connect(vlcWrapper, &VlcWrapper::started, this, &MainWindow::onPlayerStarted);
    connect(vlcWrapper, &VlcWrapper::stopped, this, &MainWindow::onPlayerStopped);
    connect(vlcWrapper, &VlcWrapper::paused, this, &MainWindow::onPlayerPaused);
    connect(vlcWrapper, &VlcWrapper::error, this, &MainWindow::onPlayerError);
}

MainWindow::~MainWindow()
{
    if(NULL!= vlcWrapper) {
        delete vlcWrapper;
    }
    if(NULL != myPaint) {
        delete myPaint;
    }
    delete timerClock;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
//    printf("resizeEvent oldSize: %d x %d", event->oldSize().width(), event->oldSize().height());
//    printf("resizeEvent newSize: %d x %d", event->size().width(), event->size().height());
}

void MainWindow::showNotation(QPixmap& pixmap) {
//    int with = ui->displayPic->width();
//    int height = ui->displayPic->height();
//    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
//    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
//    ui->displayPic->setPixmap(fitpixmap);
//    saveNotation(pixmap);
}

void MainWindow::saveNotation(QPixmap& pixmap) {

    QString filePathName = "full-";
    filePathName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
    filePathName += ".jpg";
    if(!pixmap.save(filePathName, "jpg")) {
        cout<<"save full screen failed"<<endl;
    }
}

void MainWindow::showWhiteBoard(bool state) {
    if(state) {
        ui->stackedWidget->setCurrentIndex(0);
    } else {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::on_btnPlay_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("action"),"/","",0);
    if(filename.isEmpty()) {
        return;
    }

    //ui->renderWidget->playVideo();

    filename.replace("/", "\\");
    std::string s = filename.toStdString();
    vlcWrapper->start(s, ui->myRender);
}

void MainWindow::on_btnPlayRtsp_clicked()
{
    printf("on_btnPlayRtsp_clicked");
    //vlcWrapper->start("rtsp://192.168.1.225/", ui->myRender);
}

void MainWindow::on_btnNotaion_clicked()
{
    vlcWrapper->pause();
//    ui->renderWidget->clear();
//    ui->renderWidget->loadPixmap();
}

void MainWindow::on_btnSaveNotaion_clicked()
{
//    ui->renderWidget->SavePic();
//    ui->renderWidget->clear();
    vlcWrapper->resume();
}

void MainWindow::on_takePicture()
{
//    QScreen *screen = QGuiApplication::primaryScreen();
//    QPixmap p = screen->grabWindow(0);
//    showNotation(p);
    QWidget* w = ui->stackedWidget->currentWidget();
    if(w == ui->myRender && vlcWrapper->isWorking()) {
        QImage image;
        ui->myRender->copyCurrentImage(image);
        QPixmap p =QPixmap::fromImage(image);
        savePixmap(p);
    }
    else
    {
        QPixmap p = w->grab();
        savePixmap(p);
    }
}

void MainWindow::on_btnCaptureVideo_clicked()
{
    QImage p;
    //renderWidget->getCurrentPixmap(p);
    QPixmap pixmap = QPixmap::fromImage(p);
    showNotation(pixmap);
}

void MainWindow::on_btnCapturePanel_clicked()
{
    QRect rect = ui->centralwidget->geometry();
    QPixmap p = this->grab(rect);
    showNotation(p);
    /*
    QString filePathName = "widget";
    filePathName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
    filePathName += ".png";
    if(!p.save(filePathName,"png"))
    {
        cout<<"save widget screen failed"<<endl;
    }
    */
}

void MainWindow::on_timeout()
{
//    QDateTime current_date_time = QDateTime::currentDateTime();
//    QString current_date = current_date_time.toString("hh:mm:ss");//current_date_time.toString("yyyy-MM-dd hh:mm::ss.zzz");
//    ui->labelTime->setText(current_date);
}

void MainWindow::on_btnStop_clicked()
{
    printf("on_btnStop_clicked");
//    vlcWrapper->stop();
}

void MainWindow::on_btnPlay2_clicked()
{
    //ui->renderWidget->playVideo();
    vlcWrapper->resume();
}

void MainWindow::on_btnPause_clicked()
{
    vlcWrapper->pause();
}

void MainWindow::on_btnPlayLocal_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("action"),"/","",0);
    if(filename.isEmpty()) {
        return;
    }

    filename.replace("/", "\\");
    std::string s = filename.toStdString();
    vlcWrapper->start(s, ui->myRender);
    ui->stackedWidget->setCurrentIndex(0);
    ui->toolBar->playPause()->setText(QString("暂停"));
    ui->toolBar->playPause()->setImages(QPixmap(":/images/res/images/pause.png"));
}

void MainWindow::on_btnPlayPause_clicked()
{
    printf("on_btnPlayPause_clicked");
    vlcWrapper->toggle();
//    if(vlcWrapper->isWorking()) {
//        if(vlcWrapper->isPlaying()) {
//            vlcWrapper->pause();
//            ui->toolBar->playPause()->setText(QString("播放"));
//            ui->toolBar->playPause()->setImages(QPixmap(":/images/res/images/play.png"));

//        } else {
//            vlcWrapper->resume();
//            ui->toolBar->playPause()->setText(QString("暂停"));
//            ui->toolBar->playPause()->setImages(QPixmap(":/images/res/images/pause.png"));
//        }
//    }
}

void MainWindow::on_btnComment_clicked()
{
    printf("on_btnComment_clicked");
    if(NULL == myPaint) {
        myPaint = new MyPaint(this);
        connect(myPaint, &MyPaint::quit, this, &MainWindow::on_btnComment_quit);
    }

    if (vlcWrapper->isWorking()) {
        vlcWrapper->pause();
        QImage image;
        ui->myRender->copyCurrentImage(image);
        myPaint->setImage(image);
    }

    ui->stackedWidget->addWidget(myPaint);
    ui->stackedWidget->setCurrentWidget(myPaint);
    myPaint->Lines();
    printf("ui->stackedWidget count:%d currentIndex:%d",ui->stackedWidget->count() , ui->stackedWidget->currentIndex());

//    if(ui->stackedWidget->currentIndex() == 0) {
//        if(!ui->myPaint->isCommenting()) {
//            ui->myPaint->clear();
//            ui->myPaint->Lines();
//        }
//    } else {
//        showWhiteBoard(true);
//        vlcWrapper->pause();
//        QImage image;
//        ui->myRender->copyCurrentImage(image);
//        QPixmap pixmap = QPixmap::fromImage(image);
//        ui->myPaint->clear();
//        ui->myPaint->Lines();
//        if(!pixmap.isNull()) {
//            ui->myPaint->loadPixmap(pixmap);
//        }
//    }
}

void MainWindow::on_btnComment_quit() {
    printf("on_btnComment_quit");
    ui->stackedWidget->removeWidget(myPaint);
    delete myPaint;
    myPaint = NULL;
}

void MainWindow::on_btnDevice_clicked()
{
    printf("on_btnDevice_clicked");
}

void MainWindow::onPlayerStarted() {
    printf("onPlayerStarted");
    ui->toolBar->playPause()->setText(QString("暂停"));
    ui->toolBar->playPause()->setImages(QPixmap(":/images/res/images/pause.png"));
}

void MainWindow::onPlayerStopped() {
    printf("onPlayerStopped");
    ui->toolBar->playPause()->setText(QString("播放"));
    ui->toolBar->playPause()->setImages(QPixmap(":/images/res/images/play.png"));
}

void MainWindow::onPlayerPaused() {
    printf("onPlayerPaused");
    ui->toolBar->playPause()->setText(QString("播放"));
    ui->toolBar->playPause()->setImages(QPixmap(":/images/res/images/play.png"));
}
void MainWindow::onPlayerError(QString err) {
    printf("onPlayerError");
}

