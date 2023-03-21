#ifndef CAMERAVIEWWIDGET_H
#define CAMERAVIEWWIDGET_H

#include <QWidget>
#include "model/DeviceModel.h"
#include "glvideowidget.h"
#include "FlowLayout.h"

class CameraViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraViewWidget(Device& device, QWidget *parent = nullptr);

    virtual void resizeEvent(QResizeEvent *event);
signals:

private:
    Device& device;
    GLVideoWidget* videoView;
};

#endif // CAMERAVIEWWIDGET_H
