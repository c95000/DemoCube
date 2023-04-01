#include "CameraViewWidget.h"
#include <QVBoxLayout>
#include <QLabel>

static void _ffdecoder_video_format_cb(void *opaque, int* width, int *height, int* lineSize) {
//    qDebug() << __FUNCTION__;
    CameraViewWidget* ffPlayer = qobject_cast<CameraViewWidget *>((QObject*)opaque);
    ffPlayer->videoView->setYUV420pParameters(*width, *height, lineSize);
}

static void _ffdecoder_data_available_cb(void *opaque, const QByteArray& ba) {
//    qDebug() << __FUNCTION__;
    CameraViewWidget* ffPlayer = qobject_cast<CameraViewWidget *>((QObject*)opaque);
    ffPlayer->videoView->setFrameData(ba);
}

CameraViewWidget::CameraViewWidget(Device& device, QWidget *parent)
    : QWidget{parent}, device(device)
{
    QVBoxLayout* rootLayout = new QVBoxLayout;
    setLayout(rootLayout);

    videoView = new GLVideoWidget(this);
//    QFlowLayout* controllerView = new QFlowLayout;
//    QPushButton* button1 = new QPushButton("button1");
//    controllerView->addWidget(button1);
    controllerBar = new CameraControllerV2;

    rootLayout->addStretch(1);
    rootLayout->addWidget(controllerBar);

    connect(controllerBar, &CameraControllerV2::play, this, &CameraViewWidget::play);
    connect(controllerBar, &CameraControllerV2::stop, this, &CameraViewWidget::stop);
    connect(controllerBar, &CameraControllerV2::takePicture, this, &CameraViewWidget::takePicture);
}

void CameraViewWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    videoView->resize(event->size());
}

void CameraViewWidget::play() {
    qDebug() << __FUNCTION__;
    if(nullptr == ffDecoder) {
        ffDecoder = new FFDecoder;
    }
    qDebug() << device.getUrl();
    ffDecoder->setSource(device.getUrl(), _ffdecoder_video_format_cb, _ffdecoder_data_available_cb, this);
    ffDecoder->play(true);
}
void CameraViewWidget::stop() {
    ffDecoder->stop();
}

void CameraViewWidget::takePicture() {
//    QImage img = videoView->grabFramebuffer();
//    qDebug() << img;
//    videoView->takePicture();
}

