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
#include "mainwindowv2.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationVersion(QString(APP_VERSION));
    QApplication::setApplicationName(QString("实训优学"));
//    MainWindow w;
//    PrimeWindow w;
    MainWindowV2 w;

    w.show();
    return a.exec();
}
