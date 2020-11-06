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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MainWindow w;
//    PrimeWindow w;
//    FreeDrawingMenu w;
//    LineState w;
//    FreeDrawing w;
    VlcPlayer w("C:\nginx-1.16.0\html\mfc\eb3aa50943c201336de9fa1c23b5a6c5-480p.mp4");
//      VlcPlayerController w;

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
