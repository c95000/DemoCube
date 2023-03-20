#ifndef CAMERAVIEWWIDGET_H
#define CAMERAVIEWWIDGET_H

#include <QWidget>
#include "model/DeviceModel.h"

class CameraViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraViewWidget(Device& device, QWidget *parent = nullptr);

signals:

private:
    Device& device;
};

#endif // CAMERAVIEWWIDGET_H
