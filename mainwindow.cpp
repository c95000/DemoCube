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
    , m_videobuf(NULL)
    , m_frameWidth(0)
    , m_frameHeight(0)
    , m_vlcInstance(NULL)
    , m_vlcMediaPlayer(NULL)
    , m_pvlcMedia(NULL)
{
    ui->setupUi(this);

    renderWidget = new CRenderWidget(this);
    //ui->gridLayout->addWidget(renderWidget, 0, 0);

    myPaint = new MyPaint(this);
    //ui->gridLayout->addWidget(myPaint, 0, 0);

    char const* vlc_args[] =
    {
        "-I",
        "dummy",
        "--ignore-config",
    };

    m_vlcInstance = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
    m_vlcMediaPlayer = libvlc_media_player_new (m_vlcInstance);
}

MainWindow::~MainWindow()
{
    libvlc_media_release(m_pvlcMedia);
    libvlc_media_player_stop(m_vlcMediaPlayer);
    libvlc_media_player_release(m_vlcMediaPlayer);
    libvlc_release(m_vlcInstance);
    SAFE_DELETE_ARRAY(m_videobuf);
    delete myPaint;
    delete renderWidget;
    delete ui;
}

void MainWindow::openRtsp(const char* rtsp) {
    onPause();

    m_pvlcMedia = libvlc_media_new_location(m_vlcInstance, rtsp);
    libvlc_media_player_set_media(m_vlcMediaPlayer, m_pvlcMedia);

    libvlc_video_set_callbacks(m_vlcMediaPlayer, preDecode_cb, handleStream_cb, render_cb, this);

    onPlay();
}

void MainWindow::openLocal(const char* local)
{
    onPause();

    m_pvlcMedia = libvlc_media_new_path(m_vlcInstance, local);
    libvlc_media_player_set_media(m_vlcMediaPlayer, m_pvlcMedia);

    libvlc_video_set_callbacks(m_vlcMediaPlayer, preDecode_cb, handleStream_cb, render_cb, this);

    onPlay();
}

void MainWindow::onPlay() {
    libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);

    if (state == libvlc_Playing)
    {
        return;
    }

    libvlc_media_player_play(m_vlcMediaPlayer);
    while (state == libvlc_NothingSpecial || state == libvlc_Opening)
    {
        state = libvlc_media_player_get_state(m_vlcMediaPlayer);
        MSleep(100);
    }

    if (state == libvlc_Error)
    {
        return;
    }

    libvlc_media_track_t **tracks = NULL;
    bool bFindResolution = false;

    while (!bFindResolution)
    {
        unsigned tracksCount = libvlc_media_tracks_get(m_pvlcMedia, &tracks);

        if (tracks != NULL)
        {
            for (unsigned i = 0; i < tracksCount; i++)
            {
                if (tracks[i]->i_type == libvlc_track_video
                    && tracks[i]->video->i_height != 0
                    && tracks[i]->video->i_width != 0)
                {
                    m_frameWidth = tracks[i]->video->i_width;
                    m_frameHeight = tracks[i]->video->i_height;
                    bFindResolution = true;
                    break;
                }
            }
        }

        libvlc_media_tracks_release(tracks, tracksCount);
        MSleep(100);
    }

    // [workaround]: I don't know how to change format (libvlc_video_set_format) after playing...
    // reconnect the stream
    libvlc_media_player_stop(m_vlcMediaPlayer);

    libvlc_video_set_format(m_vlcMediaPlayer, "RV32", m_frameWidth, m_frameHeight, m_frameWidth << 2);
    SAFE_DELETE_ARRAY(m_videobuf);
    allocVideoBuf(m_frameWidth, m_frameHeight);

    libvlc_media_player_play(m_vlcMediaPlayer);
}

void MainWindow::onPause() {
    libvlc_media_player_pause(m_vlcMediaPlayer);
}

void MainWindow::onResume() {
    libvlc_media_player_play(m_vlcMediaPlayer);
}


void* MainWindow::preDecode_cb(void *opaque, void **planes)
{
    MainWindow* obj = (MainWindow*)opaque;
    *planes = obj->getVideoBuf();

    return obj->getVideoBuf();
}

void MainWindow::handleStream_cb(void *opaque, void *picture, void *const *planes)
{
    Q_UNUSED(opaque);
    Q_UNUSED(picture);
    Q_UNUSED(planes);
    // TODO - image processing
//     if (picture != NULL)
//     {
//         CPlayerView* obj = (CPlayerView*)opaque;
//         Mat img(Size(obj->m_frameWidth, obj->m_frameHeight), CV_8UC4, picture);
//
//         imshow("123", img);
//         waitKey(1);
//     }
}

void MainWindow::render_cb(void *opaque, void *picture)
{
    MainWindow* obj = (MainWindow*)opaque;
    QImage qimg((uchar*)picture, obj->m_frameWidth, obj->m_frameHeight, QImage::Format_ARGB32);;
    obj->renderWidget->setPixmap(qimg);
}

void MainWindow::allocVideoBuf(int width, int height)
{
    m_videobuf = new char[(width * height) << 2];
}

char* MainWindow::getVideoBuf() const
{
    return m_videobuf;
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
    if(ui->gridLayout->isEmpty()) {
        ui->gridLayout->addWidget(renderWidget, 0, 0);
        return;
    }
    QWidget* widget = ui->gridLayout->itemAtPosition(0, 0)->widget();
    if(nullptr != widget) {
        ui->gridLayout->removeWidget(widget);
        widget->setParent(nullptr);
        if(widget == renderWidget) {
            //onPause();
            ui->gridLayout->addWidget(myPaint, 0, 0);
        } else if(widget == myPaint) {
            ui->gridLayout->addWidget(renderWidget, 0, 0);
            //onResume();
        }
        ui->gridLayout->update();
    }

}

void MainWindow::on_btnPlay_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("action"),"/","",0);
    if(filename.isEmpty()) {
        return;
    }
    filename.replace("/", "\\");
    std::string s = filename.toStdString();
    const char* videoPath = s.c_str();
    openLocal(videoPath);
}

void MainWindow::on_btnPlayRtsp_clicked()
{
    openRtsp("rtsp://192.168.1.225/");
}

void MainWindow::on_btnNotaion_clicked()
{
    QWidget* widget = ui->gridLayout->itemAtPosition(0, 0)->widget();
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
    renderWidget->getCurrentPixmap(p);
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




