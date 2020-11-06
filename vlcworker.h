#ifndef VLCWORKER_H
#define VLCWORKER_H

#include <QObject>
#include "vlc/vlc.h"
#include <QThread>

class VlcWorker : public QObject
{
    Q_OBJECT

public:
    explicit VlcWorker(const QString& inputsource, QObject *parent = nullptr);
    ~VlcWorker();

public slots:
    void onPlay();
    void onStop();
    void onPause();
    void onResume();
    void onExit();

signals:
    void prepared();
    void started();
    void paused();
    void stopped();

//protected:
//    virtual void run();

private:
    void initVlc();
    void deinitVlc();

public:
    char * m_videobuf;

private:
    QString inputSource;

    libvlc_instance_t* m_vlcInstance;
    libvlc_media_player_t* m_vlcMediaPlayer;
    libvlc_media_t* m_pvlcMedia;

    QThread *worker;


};

#endif // VLCWORKER_H
