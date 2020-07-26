#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTime>
#include <QScreen>
#include <QLabel>
#include "Util.h"
#include<iostream>
#include "common.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

//    QPalette pal(palette());
//    pal.setColor(QPalette::Background, QColor(135,206,235)); //设置背景黑色
//    setAutoFillBackground(true);
//    setPalette(pal);

    ui->setupUi(this);

    connect(ui->toolBar->whiteBoardButton(), &QPushButton::clicked, this, &MainWindow::on_btnWhiteBoard_clicked);
    connect(ui->toolBar->insertButton(), &QPushButton::clicked, this, &MainWindow::on_btnPlayLocal_clicked);
    connect(ui->toolBar->commentButton(), &QPushButton::clicked, this, &MainWindow::on_btnComment_clicked);
    connect(ui->toolBar->capturePictureButton(), &QPushButton::clicked, this, &MainWindow::on_btnDevice_clicked);

    connect(ui->mediaController->playPauseButton(), &QPushButton::clicked, this, &MainWindow::on_btnPlayPause_clicked);
    connect(ui->mediaController->stopButton(), &QPushButton::clicked, this, &MainWindow::on_btnStop_clicked);

    ui->videoButton1->setText("视频1");
    ui->videoButton2->setText("视频2");

//    myPaint = new MyPaint(this);
//    myPaint->setParent(nullptr);

//    myNotation = new MyPaint(this);
//    myNotation->setParent(nullptr);
    //ui->gridLayout->addWidget(myPaint, 0, 0);

    timerClock = new QTimer();
    connect(timerClock,  SIGNAL(timeout()), this, SLOT(on_timeout()));
    timerClock->setInterval(1000);
    vlcWrapper = new VlcWrapper();
}

MainWindow::~MainWindow()
{
    if(NULL!= vlcWrapper) {
        delete vlcWrapper;
    }
//    delete myPaint;
//    delete myNotation;
    delete timerClock;
    delete ui;
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

void MainWindow::on_btnCaptureScreen_clicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap p = screen->grabWindow(0);
    showNotation(p);
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

void MainWindow::on_btnWhiteBoard_clicked()
{
    printf("on_btnWhiteBoard_clicked");
    vlcWrapper->pause();

    ui->myPaint->clear();

//    int nCount = ui->stackedWidget->count();
//    int nIndex = ui->stackedWidget->currentIndex();

//    // 获取下一个需要显示的页面索引
//    ++nIndex;

//    // 当需要显示的页面索引大于等于总页面时，切换至首页
//    if (nIndex >= nCount)
//        nIndex = 0;

    ui->stackedWidget->setCurrentIndex(0);

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
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnPlayPause_clicked()
{
    printf("on_btnPlayPause_clicked");
}

void MainWindow::on_btnComment_clicked()
{
    printf("on_btnComment_clicked");
    showWhiteBoard(true);
    vlcWrapper->pause();
    QImage image;
    ui->myRender->copyCurrentImage(image);
    QPixmap pixmap = QPixmap::fromImage(image);
    ui->myPaint->clear();
    ui->myPaint->loadPixmap(pixmap);
}

void MainWindow::on_btnDevice_clicked()
{
    printf("on_btnDevice_clicked");
}
