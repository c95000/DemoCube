#ifndef FFPLAYER_H
#define FFPLAYER_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QFile>
#include "ffdecoder.h"
#include "glvideowidget.h"

class FFPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit FFPlayer(QWidget *parent = nullptr);
    explicit FFPlayer(const QString& inputSrc, QWidget *parent = nullptr);
    ~FFPlayer();
private:
    void init();

signals:
    void prepared();
    void played();
    void paused();
    void stopped();
    void startRecorded();
    void stopRecorded();

public slots:
    void play(const QString& ip);
    void play();
    void stop();
    void pause();
    void close();
    void takePicture();
    void comment();

    void startRecord();
    void stopRecord();

    void rotation();
public:
    const QPixmap snapshot();
    void setVideoSize(int width, int height);

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);

public:
    GLVideoWidget* videoView;

private:
    QString inputSource; // media source

    FFDecoder* ffDecoder;
    int videoWidth = 16;
    int videoHeight = 9;
};

#endif // FFPLAYER_H
