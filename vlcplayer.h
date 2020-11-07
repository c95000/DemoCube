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
    explicit VlcPlayer(const QString& inputSrc, QWidget *parent = nullptr);
    ~VlcPlayer();

public:
    void start();
    void stop();
    void pause();
    void resume();

public slots:
    void onPlay();
    void onStop();

signals:
    void prepared();
    void started();
    void paused();
    void stopped();

public:
    char * m_videobuf;

private:
    Ui::VlcPlayer *ui;

    GLVideoWidget* m_videoView;
    QString inputSource;
    VlcWorker *worker;
    VlcPlayerController *controller;
    QThread *childThread;
    Loading *loading;
};

#endif // VLCPLAYER_H
