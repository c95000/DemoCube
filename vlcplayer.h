#ifndef VLCPLAYER_H
#define VLCPLAYER_H

#include <QWidget>
#include "glvideowidget.h"
#include "vlc/vlc.h"
#include "vlcworker.h"
#include "vlcplayercontroller.h"
#include "Loading/Loading.h"

namespace Ui {
class VlcPlayer;
}

class VlcPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VlcPlayer(QWidget *parent = nullptr);
    explicit VlcPlayer(const QString& inputSrc, QWidget *parent = nullptr);
    ~VlcPlayer();

private:
    void init();

public:
//    void start();
//    void stop();
//    void pause();
//    void resume();

public slots:
    void play(const QString& inputSrc);
    void play();
    void stop();
    void pause();
    void close();
    void takePicture();
    void comment();

signals:
    void prepared();
    void played();
    void paused();
    void stopped();

public:
    const QPixmap snapshot();

private:
    Ui::VlcPlayer *ui;

    QWidget* videoView;
    QString inputSource; // media filename

    libvlc_instance_t* m_vlcInstance;
    libvlc_media_player_t* m_vlcMediaPlayer;
    libvlc_media_t* m_vlcMedia;

    Loading *loading;

    int64_t duration;
    QSize videoSize;
};

#endif // VLCPLAYER_H
