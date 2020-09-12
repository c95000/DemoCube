#ifndef JYPLAYER_H
#define JYPLAYER_H

#include <QObject>
#include <QThread>
#include "glvideowidget.h"

extern "C"
{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
    #include "libavdevice/avdevice.h"
    #include "libavutil/opt.h"
}

class JyPlayer : public QThread
{
    Q_OBJECT
public:
    explicit JyPlayer(const QString& inputsource, QObject *parent = nullptr);

signals:

protected:
    void run() override;

public:
    int startPlay(GLVideoWidget* glVideoWidget);
    int startPlay();
    int stopPlay();

private:
    QString source;
    int state;

    GLVideoWidget* glVideoWidget;
    QString h264FileName;
};

#endif // JYPLAYER_H
