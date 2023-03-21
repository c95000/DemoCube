#include "CameraViewWidget.h"
#include <QVBoxLayout>
#include <QLabel>


CameraViewWidget::CameraViewWidget(Device& device, QWidget *parent)
    : QWidget{parent}, device(device)
{
    QVBoxLayout* rootLayout = new QVBoxLayout;
    setLayout(rootLayout);

//        QLabel* title = new QLabel();
//        title->setText(device.ip);
//        rootLayout->addWidget(title, 0, Qt::AlignHCenter);

    videoView = new GLVideoWidget(this);
    QFlowLayout* controllerView = new QFlowLayout;
    rootLayout->addStretch(1);
    rootLayout->addLayout(controllerView);
    QPushButton* button1 = new QPushButton("button1");
    controllerView->addWidget(button1);
    connect(button1, &QPushButton::clicked, this, [=]() {
        qDebug() << __FUNCTION__;
        qDebug() << device.getUrl();
    });
}

void CameraViewWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    videoView->setFixedSize(event->size());
}
