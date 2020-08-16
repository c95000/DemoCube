#ifndef VIDEORENDERCALLBACK_H
#define VIDEORENDERCALLBACK_H

#include <QImage>

class VideoRenderCallback {
public:
//    virtual void onVideoDataAvailable(const QImage &pixmap) = 0;
    virtual void renderYUV(uchar* ptr, long size, int width,int height,int type) = 0;
    virtual void renderYUV(QByteArray& ptr,int width,int height,int type) = 0;
    virtual void onRender(const QImage &pixmap) = 0;
};

#endif // VIDEORENDERCALLBACK_H
