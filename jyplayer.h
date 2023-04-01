#ifndef JYPLAYER_H
#define JYPLAYER_H

#include <QObject>
#include <QThread>
#include <QFile>
#include "glvideowidget.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QThread>
extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libswscale/swscale.h>
    #include <libavutil/imgutils.h>
}
enum enJYPLAYER_STATE {
    IDLE = 0,
    PREPARING,
    PLAYING,
    PAUSED,
    STOPPED,

};

class JyPlayer : public QThread
{
    Q_OBJECT
public:
    explicit JyPlayer(const QString& inputsource, QObject *parent = nullptr);

signals:
    void started();
    void paused();
    void stopped();
    void error(QString& err);

    void recordStarted();

protected:
    void run() override;

public:
    int startPlay(const QString& inputsource, GLVideoWidget* glVideoWidget);
    int startPlay();
    int stopPlay();
    int pausePlay();
    int resumePlay();
    int togglePlay();

    bool isWorking();

    int startRecord();
    int stopRecord();

private:
    void setState(enJYPLAYER_STATE state);
    int playDirectly(const char *source);

private:
    QString source;
    enJYPLAYER_STATE state;

    GLVideoWidget* glVideoWidget;
    QString h264FileName;

    bool isRecording = false;
    bool isGotIFrame = false;
    QString recordedFileName;
    FILE *h264File;
    QFile qh264File;

    bool playing;
};

#endif // JYPLAYER_H
