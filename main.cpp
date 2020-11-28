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
#include "cameracontroller1.h"
#include "recordindicator.h"
#include "progressbar.h"
#include "iconbutton.h"
#include <QQuickWidget>
#include "penstyle.h"
#include "penstate.h"
#include "assist.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MainWindow w;
    PrimeWindow w;
//    FreeDrawingMenu w;
//    LineState w;
//    FreeDrawing w;
//    VlcPlayer w(QString("C:\\nginx-1.16.0\\html\\mfc\\20s_video.mp4"));
//    VlcPlayerController w;
//    ImageDisplay w;
//    CameraController1 w;
//    RecordIndicator w;
//    VlcPlayerController w;
//    ProgressBar w;
//    PenStyle w;
//    PenState w(Qt::yellow, 15);
//    Assist w;

    //    QIcon icon1;
    //    icon1.addFile(":/res/icons/account_circle_outline.svg");

    //    QIcon icon2;
    //    icon2.addFile(":/res/icons/account_circle.svg");
//    IconButton w(QString(":/res/icons/account_circle_outline.svg"), QString(":/res/icons/account_circle.svg"));
//    IconButton w(QString(":/res/icons/connect_camera_o.svg"), QString(":/res/icons/connect_camera.svg"));
//    Navigator w;
//    FFPlayer w(QString("C:\\nginx-1.16.0\\html\\mfc\\20s_video.mp4"));

//    QQuickWidget *view = new QQuickWidget;
//    view->setSource(QUrl::fromLocalFile(":SvgAttr.qml"));
//    view->show();


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
