#include <QApplication>
#include <QSize>
#include "ui/homev2_2.h"
#include "mainwindowv12.h"
#include "ui/TestViewController.h"
#include "ui/MainUI.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    TestViewController w;
//    MainWindowV12 w;
    HomeV2_2 w;
    QSize size = QSize(16, 9).scaled(QSize(1280, 1280), Qt::KeepAspectRatio);
    w.resize(size);
    w.show();
    return a.exec();
}
