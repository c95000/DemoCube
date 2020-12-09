#include <QApplication>
#include "ffplayer.h"
#include "cameracontroller1.h"
#include "recordindicator.h"
#include "progressbar.h"
#include "firstwindow.h"
#include "sockettest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FirstWindow w;
    w.show();
    return a.exec();
}
