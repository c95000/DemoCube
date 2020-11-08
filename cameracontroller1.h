#ifndef CAMERACONTROLLER1_H
#define CAMERACONTROLLER1_H

#include <QWidget>
#include "common.h"
#include <QObject>
class CameraController1 : public QWidget
{
    Q_OBJECT
public:
    explicit CameraController1(QWidget *parent = nullptr);
    explicit CameraController1(const QString& url, QWidget *parent = nullptr);
    ~CameraController1();

//private:
    void init();

signals:
    void signalConnect();
    void signalConnect(const QString& url);
    void signalDisconnect();
    void play();
    void pause();
    void takePicture();
    void comment();

public slots:
    void onConnect(const QString& sourceUrl);
    void onDisconnect();

private:
    QPushButton *btnConnect;
    QPushButton *btnPlay;
    QPushButton *btnPause;
    QPushButton *btnDisconnect;
    QPushButton *btnTakePicture;
    QPushButton *btnComment;
    QPushButton *btnExit;

    QString sourceUrl;
};

#endif // CAMERACONTROLLER1_H
