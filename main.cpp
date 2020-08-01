#include "mainwindow.h"

#include <QApplication>
#include <ToolBar.h>
#include <CommentToolBar.h>
#include <mypaint.h>
#include <CameraController.h>
#include <CameraManager.h>
//#include <scaler.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Scaler s(&a);


    MainWindow w;
    w.showMaximized();
//    w.show();

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

    return a.exec();
}
