#include "CameraControllerV2.h"

CameraControllerV2::CameraControllerV2(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout *rootLayout = new QHBoxLayout;
    setLayout(rootLayout);

//    TouchButton* connectButton = new TouchButton("连接");
    playpauseButton = new TouchButton("播放");
    TouchButton* stopButton = new TouchButton("停止");
    TouchButton* takePictureButton = new TouchButton("拍照");

    rootLayout->addWidget(playpauseButton);
    rootLayout->addWidget(stopButton);
     rootLayout->addWidget(takePictureButton);
    connect(playpauseButton, &QPushButton::clicked, this, [=]() {
        emit play();
    });
    connect(stopButton, &QPushButton::clicked, this, [=]() {
        emit stop();
    });
    connect(takePictureButton, &QPushButton::clicked, this, [=]() {
        emit takePicture();
    });
}

void CameraControllerV2::setPlayed(bool state) {
    played = state;
}
