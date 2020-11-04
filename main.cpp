#include "mainwindow.h"

#include <QApplication>
#include <ToolBar.h>
#include <CommentToolBar.h>
#include <mypaint.h>
#include <CameraController.h>
#include <CameraManager.h>
#include "recordlabel.h"
#include "primewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MainWindow w;
    PrimeWindow w;

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
