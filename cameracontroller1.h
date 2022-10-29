﻿#ifndef CAMERACONTROLLER1_H
#define CAMERACONTROLLER1_H

#include <QWidget>
#include "common.h"
#include <QObject>
#include "recordindicator.h"
#include "iconbutton.h"

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
    void signalConnect(const int index);
    void signalDisconnect();
    void play();
    void pause();
    void takePicture();
    void comment();

    void startRecord();
    void stopRecord();

    void zoomWide();
    void zoomTele();
    void zoomStop();

    void rotation();
    void releaseButton(int);

public slots:
    void connected();
    void disconnected();
    void played();
    void paused();
    void stopped();
    void connectFailed(int index);

private slots:
    void startRecorded();
    void stopRecorded();
    void onButtonToggled(int index, bool);
    void onButtonPressed(int index);

    void connectSource(int index);

private:
    QButtonGroup *buttonGround;

    IconButton *btnConnect1;
    IconButton *btnConnect2;
    IconButton *btnConnect3;
    QPushButton *btnPlay;
    QPushButton *btnPause;
    IconButton *btnDisconnect;
    IconButton *btnTakePicture;
    IconButton *btnComment;
    QPushButton *btnExit;
    IconButton *btnZoomWide; // 缩小
    IconButton *btnZoomTele; // 放大

    IconButton *btnRotation; // 放大

    IconButton *btnStartRecord;
    IconButton *btnStopRecord;
    RecordIndicator *recordIndicator;

    QString sourceUrl;
};

#endif // CAMERACONTROLLER1_H
