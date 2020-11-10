#ifndef CAMERACONTROLLER1_H
#define CAMERACONTROLLER1_H

#include <QWidget>
#include "common.h"
#include <QObject>
#include "recordindicator.h"

class CameraController1 : public QWidget
{
    Q_OBJECT
public:
    explicit CameraController1(QWidget *parent = nullptr);
    explicit CameraController1(const QString& url, QWidget *parent = nullptr);
    ~CameraController1();

//private:
    void init();

protected:
    void resizeEvent(QResizeEvent *event);

signals:
    void signalConnect();
    void signalConnect(const QString& url);
    void signalDisconnect();
    void play();
    void pause();
    void takePicture();
    void comment();

public slots:
    void connected();
    void disconnected();
    void played();
    void paused();
    void stopped();

private slots:
    void startRecord();
    void stopRecord();

private:
    QPushButton *btnConnect;
    QPushButton *btnPlay;
    QPushButton *btnPause;
    QPushButton *btnDisconnect;
    QPushButton *btnTakePicture;
    QPushButton *btnComment;
    QPushButton *btnExit;

    QPushButton *btnStartRecord;
    QPushButton *btnStopRecord;
    RecordIndicator *recordIndicator;

    QString sourceUrl;
};

#endif // CAMERACONTROLLER1_H
