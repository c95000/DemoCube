#include "scaler.h"
#include <QDesktopWidget>
#include "common.h"

Scaler::Scaler(QApplication *app) : QObject(nullptr)
{
    this->desktopWidget = app->desktop();

    printf("Scaler desktop: %d x %d", desktopWidget->width(), desktopWidget->height());

    sx = desktopWidget->width() / 1920.0;
    if(sx <= 0) {
        sx = 1.0;
    }
    sy = desktopWidget->height() / 1080.0;
    if(sy <= 0) {
        sy = 1.0;
    }

    printf("Scaler: %lf x %lf", sx, sy);
}


//Scaler::~Scaler()
//{
//}

double Scaler::scaleX() {
    return sx;
}

double Scaler::scaleY() {
    return sy;
}
