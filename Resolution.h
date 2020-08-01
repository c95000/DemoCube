#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "common.h"
#include <QApplication>
#include <QDesktopWidget>

class Resolution
{
//public:
//    Resolution();
private:
    Resolution()
    {
        int desktop_width = QApplication::desktop()->width();
        int desktop_height = QApplication::desktop()->height();
        printf("desktop %d x %d", desktop_width, desktop_height);

        sx = desktop_width / 1920.0;
        if(sx <= 0) {
            sx = 1.0;
        }
        sy = desktop_height / 1080.0;
        if(sy <= 0) {
            sy = 1.0;
        }

        printf("Resolution: %lf x %lf", sx, sy);
    }
    static Resolution *p;

public:
    static Resolution* getInstance()
    {
        if(p == nullptr)
            p = new Resolution();
        return p;
    }

public:
    double scaleX();
    double scaleY();

private:
    double sx;
    double sy;
};

#endif // RESOLUTION_H
