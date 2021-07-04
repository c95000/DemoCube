#ifndef VLCTEST_H
#define VLCTEST_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "vlc/vlc.h"
#include "glvideowidget.h"
#include <QMutex>
class VlcTest : public QWidget
{
    Q_OBJECT
public:
    explicit VlcTest(QWidget *parent = nullptr);
    ~VlcTest();

signals:

private:
    void play();
    void pause();
    void stop();
    void test();

public:
    void updatePos();

private:
    QString fileName;

    libvlc_instance_t* m_vlcInstance;
    libvlc_media_player_t* m_vlcMediaPlayer;
    libvlc_media_t* m_vlcMedia;

    int frameCount = 0;
public:
    GLVideoWidget* videoView;
    QMutex mutex;

};

#endif // VLCTEST_H
