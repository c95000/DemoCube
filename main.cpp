#include "mainwindow.h"

#include <QApplication>
#include <ToolBar.h>
#include <CommentToolBar.h>
#include <mypaint.h>
#include <CameraController.h>
#include <CameraManager.h>
#include "recordlabel.h"
#include "primewindow.h"
#include "freedrawingmenu.h"
#include "linestate.h"
#include "freedrawing.h"
#include "vlcplayer.h"
#include "vlcplayercontroller.h"
#include "imagedisplay.h"
#include "navigator.h"
#include "ffplayer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MainWindow w;
//    PrimeWindow w;
//    FreeDrawingMenu w;
//    LineState w;
//    FreeDrawing w;
//    VlcPlayer w(QString("C:\\nginx-1.16.0\\html\\mfc\\20s_video.mp4"));
//    VlcPlayerController w;
//    ImageDisplay w;

//    Navigator w;
    FFPlayer w(QString("C:\\nginx-1.16.0\\html\\mfc\\20s_video.mp4"));

//    ToolBar w;
//    w.show();

//    CommentToolBar w;
//    w.show();

//    MyPaint mypaint;
//    mypaint.show();

//    CameraController cameraController;
//    cameraController.show();

//    QWidget qq;
//    qq.show();

//    CameraManager cm;
//    cm.show();

//    RecordLabel r;
//    r.show();

    w.show();
    return a.exec();
}
