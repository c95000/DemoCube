#include "mainwindow.h"

#include <QApplication>
#include <ToolBar.h>
#include <CommentToolBar.h>
#include <mypaint.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    ToolBar w;
//    w.show();

//    CommentToolBar w;
//    w.show();

    MyPaint mypaint;
    mypaint.show();
    return a.exec();
}
