#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "Util.h"

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
    delete ui;
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

void MainWindow::openRtsp(const char* rtsp) {

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
    //obj->ui->renderWidget->setPixmap(qimg);
}

void MainWindow::allocVideoBuf(int width, int height)
{
    m_videobuf = new char[(width * height) << 2];
}

char* MainWindow::getVideoBuf() const
{
    return m_videobuf;
}
