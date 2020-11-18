#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QMainWindow>
#include "common.h"
#include "glvideowidget.h"
#include "cameracontroller1.h"
#include "ffplayer.h"
//#include "ArnetWrapper.h"
#include "sockettest.h"

class FirstWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit FirstWindow(QWidget *parent = nullptr);
    virtual ~FirstWindow();
signals:

private slots:
    void onZoomin();
    void onZoomout();
    void onError(int);

private:
    GLVideoWidget *videoView;
    CameraController1 *cameraController;
    FFPlayer *ffplayer;
//    ArnetWrapper *arnetWrapper;
    SocketTest *socketTest;
};

#endif // FIRSTWINDOW_H
