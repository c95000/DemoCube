#include "CameraViewWidget.h"
#include <QVBoxLayout>
#include <QLabel>

static void _ffdecoder_video_format_cb(void *opaque, int* width, int *height, int* lineSize) {
//    qDebug() << __FUNCTION__;
    CameraViewWidget* ffPlayer = qobject_cast<CameraViewWidget *>((QObject*)opaque);
//    FFPlayer* ffPlayer = (FFPlayer*)opaque;
//    printf("*video size: %d x %d lineSize: %d / %d / %d", *width, *height, lineSize[0], lineSize[1], lineSize[2]);
//    ffPlayer->setVideoSize(*width, *height);
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

//        QLabel* title = new QLabel();
//        title->setText(device.ip);
//        rootLayout->addWidget(title, 0, Qt::AlignHCenter);

    videoView = new GLVideoWidget(this);
//    videoRender = new VideoGLRender(this);
    QFlowLayout* controllerView = new QFlowLayout;
    rootLayout->addStretch(1);
//    rootLayout->addWidget(videoView, 1);
//    rootLayout->addWidget(videoRender, 1);
    rootLayout->addLayout(controllerView);
    QPushButton* button1 = new QPushButton("button1");
    controllerView->addWidget(button1);
    connect(button1, &QPushButton::clicked, this, [=]() {
        qDebug() << __FUNCTION__;
        qDebug() << device.getUrl();
        ffDecoder->setSource(device.getUrl(), _ffdecoder_video_format_cb, _ffdecoder_data_available_cb, this);
        ffDecoder->play(true);
    });

    ffDecoder = new FFDecoder();
}

void CameraViewWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    videoView->resize(event->size());
}
