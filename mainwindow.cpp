#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTime>
#include <QScreen>
#include <QLabel>
#include "Util.h"
#include<iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myPaint = new MyPaint(this);
    myPaint->setParent(nullptr);

    myNotation = new MyPaint(this);
    myNotation->setParent(nullptr);
    //ui->gridLayout->addWidget(myPaint, 0, 0);

    timerClock = new QTimer();
    connect(timerClock,  SIGNAL(timeout()), this, SLOT(on_timeout()));
    timerClock->setInterval(1000);
    vlcWrapper = new VlcWrapper();
}

MainWindow::~MainWindow()
{
    delete vlcWrapper;
    delete myPaint;
    delete myNotation;
    delete timerClock;
    delete ui;
}

void MainWindow::showNotation(QPixmap& pixmap) {
    int with = ui->displayPic->width();
    int height = ui->displayPic->height();
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->displayPic->setPixmap(fitpixmap);
    saveNotation(pixmap);
}

void MainWindow::saveNotation(QPixmap& pixmap) {

    QString filePathName = "full-";
    filePathName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
    filePathName += ".jpg";
    if(!pixmap.save(filePathName, "jpg")) {
        cout<<"save full screen failed"<<endl;
    }
}

void MainWindow::on_btnShowPanel_clicked()
{
    //ui->renderWidget->setPixmap();
}

void MainWindow::on_btnPlay_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("action"),"/","",0);
    if(filename.isEmpty()) {
        return;
    }
    filename.replace("/", "\\");
    std::string s = filename.toStdString();
    vlcWrapper->start(s, ui->renderWidget);
}

void MainWindow::on_btnPlayRtsp_clicked()
{
    vlcWrapper->start("rtsp://192.168.1.225/", ui->renderWidget);
}

void MainWindow::on_btnNotaion_clicked()
{
    QWidget* widget = ui->gridLayout->itemAtPosition(0, 0)->widget();
    if(nullptr == widget) {
        return;
    }
#if 0
    if(widget == renderWidget) {
        onPause();
        QImage p;
        renderWidget->getCurrentPixmap(p);
        QPixmap pixmap = QPixmap::fromImage(p);
        showNotation(pixmap);

        ui->gridLayout->removeWidget(widget);
        widget->setParent(nullptr);
        ui->gridLayout->addWidget(myPaint, 0, 0);
        ui->gridLayout->update();
        myPaint->loadPixmap(pixmap);
    }
#endif
#if 0
    if(nullptr != widget) {
        ui->gridLayout->removeWidget(widget);
        if(widget == renderWidget) {
            onPause();
            QImage p;
            renderWidget->getCurrentPixmap(p);
            QPixmap pixmap = QPixmap::fromImage(p);
            showNotation(pixmap);
        } else if(widget == myPaint) {
            QRect rect = ui->centralwidget->geometry();
            QPixmap p = this->grab(rect);
            showNotation(p);
            onResume();
        }
    }
#endif
}

void MainWindow::on_btnSaveNotaion_clicked()
{

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
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("hh:mm:ss");//current_date_time.toString("yyyy-MM-dd hh:mm::ss.zzz");
    ui->labelTime->setText(current_date);
}

void MainWindow::on_btnStop_clicked()
{
    vlcWrapper->stop();
}

void MainWindow::on_btnPlay2_clicked()
{
    vlcWrapper->resume();
}

void MainWindow::on_btnPause_clicked()
{
    vlcWrapper->pause();
}
