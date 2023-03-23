#ifndef CAMERAVIEWWIDGET_H
#define CAMERAVIEWWIDGET_H

#include <QWidget>
#include "model/DeviceModel.h"
#include "glvideowidget.h"
#include "FlowLayout.h"
#include "ffdecoder.h"
#include "VideoGLRender.h"
class CameraViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraViewWidget(Device& device, QWidget *parent = nullptr);

    virtual void resizeEvent(QResizeEvent *event);
signals:

public:
    GLVideoWidget* videoView;
    VideoGLRender* videoRender;
private:
    Device& device;


    FFDecoder* ffDecoder;
    int videoWidth = 16;
    int videoHeight = 9;
};

#endif // CAMERAVIEWWIDGET_H
