#include <QApplication>
#include <QSize>
#include "ui/homev2_2.h"
#include "mainwindowv12.h"
#include "ui/TestViewController.h"
#include "ui/MainUI.h"
#include "ui/TopBar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    HomeV2_2 w;
//    MainUI w;
    TopBar w;
    QSize size = QSize(16, 9).scaled(QSize(1280, 1280), Qt::KeepAspectRatio);
    w.resize(size);
    w.show();
    return a.exec();
}
