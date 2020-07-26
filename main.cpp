#include "mainwindow.h"

#include <QApplication>
#include <ToolBar.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    ToolBar w;
//    w.show();
    return a.exec();
}
