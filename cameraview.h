#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QObject>
#include <QWidget>
#include "vlc/vlc.h"

class CameraView : public QWidget
{
    Q_OBJECT
public:
    explicit CameraView(QWidget *parent = nullptr);
    ~CameraView();

signals:
    void prepared();
    void played();
    void paused();
    void stopped();

public slots:
    void onConnect(const QString& sourceUrl);
    void onDisconnect();
    void pause();
    void play();
    void takePicture();

public:
    const QPixmap snapshot();

private:
    void play(const QString& inputSrc);
    void stop();

private:
    QString sourceUrl;
    QWidget* videoView;

    libvlc_instance_t* m_vlcInstance;
    libvlc_media_player_t* m_vlcMediaPlayer;
    libvlc_media_t* m_vlcMedia;
};

#endif // CAMERAVIEW_H
