#include "CameraViewWidget.h"
#include <QVBoxLayout>
#include <QLabel>


CameraViewWidget::CameraViewWidget(Device& device, QWidget *parent)
    : QWidget{parent}, device(device)
{
    QVBoxLayout* rootLayout = new QVBoxLayout;
    setLayout(rootLayout);

    QLabel* title = new QLabel();
    title->setText(device.ip);
    rootLayout->addWidget(title, 0, Qt::AlignCenter);
}
