#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vlc/vlc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnPlay_clicked();

private:
    void openRtsp(const char* rtsp);
    void openLocal(const char* local);

    void onPlay();
    void onPause();
    static void* preDecode_cb(void *opaque, void **planes);
    static void handleStream_cb(void *opaque, void *picture, void *const *planes);
    static void render_cb(void *opaque, void *picture);

    void allocVideoBuf(int width, int height);
    char* getVideoBuf() const;

private:
    Ui::MainWindow *ui;

    char * m_videobuf;
    int m_frameWidth;
    int m_frameHeight;

    libvlc_instance_t* m_vlcInstance;
    libvlc_media_player_t* m_vlcMediaPlayer;
    libvlc_media_t* m_pvlcMedia;

};
#endif // MAINWINDOW_H
