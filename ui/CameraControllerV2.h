#ifndef CAMERACONTROLLERV2_H
#define CAMERACONTROLLERV2_H

#include <QWidget>
#include <QHBoxLayout>
#include "TouchButton.h"

class CameraControllerV2 : public QWidget
{
    Q_OBJECT
public:
    explicit CameraControllerV2(QWidget *parent = nullptr);
    void setPlayed(bool state);
signals:
    void play();
    void stop();
    void takePicture();
private:
    bool played = false;
    TouchButton* playpauseButton;
};

#endif // CAMERACONTROLLERV2_H
