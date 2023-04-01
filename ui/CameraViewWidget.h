#ifndef CAMERAVIEWWIDGET_H
#define CAMERAVIEWWIDGET_H

#include <QWidget>
#include "model/DeviceModel.h"
#include "glvideowidget.h"
#include "FlowLayout.h"
#include "ffdecoder.h"
#include "VideoGLRender.h"
#include "CameraControllerV2.h"

class CameraViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraViewWidget(Device& device, QWidget *parent = nullptr);

    virtual void resizeEvent(QResizeEvent *event);
signals:

private slots:
    void play();
    void stop();
    void takePicture();

public:
    GLVideoWidget* videoView;
    VideoGLRender* videoRender;
private:
    Device& device;
    FFDecoder* ffDecoder = NULL;
    int videoWidth = 16;
    int videoHeight = 9;
    CameraControllerV2* controllerBar;
};

#endif // CAMERAVIEWWIDGET_H
