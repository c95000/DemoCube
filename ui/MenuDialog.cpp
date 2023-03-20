#include "MenuDialog.h"
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include "utils/ThemeUtils.h"
#include "ui/TouchButton.h"

MenuDialog::MenuDialog(QWidget *parent)
    : QWidget{parent}
{
//    this->setWindowFlags(Qt::Popup);
    ThemeUtils::setBackground(this, 0x888888, 0.5);
    QVBoxLayout* rootLayout = new QVBoxLayout;
    setLayout(rootLayout);

    //    TouchButton* button1 = new TouchButton("button1");
    //    TouchButton* button2 = new TouchButton("button2");
    //    TouchButton* button3 = new TouchButton("button3");

    //    rootLayout->addStretch(1);
    //    rootLayout->addWidget(button1, 0, Qt::AlignCenter);
    //    rootLayout->addWidget(button2, 0, Qt::AlignCenter);
    //    rootLayout->addWidget(button3, 0, Qt::AlignCenter);
    //    rootLayout->addStretch(1);

    //    connect(button1, &QPushButton::clicked, this, [=]() {
    //        emit onButtonClicked(0);
    //    });
    //    connect(button2, &QPushButton::clicked, this, [=]() {
    //        emit onButtonClicked(1);
    //    });
    //    connect(button3, &QPushButton::clicked, this, [=]() {
    //        emit onButtonClicked(2);
    //    });

    initView();

    connect(&deviceModel, &DeviceModel::dataChanged, this, [=]() {
        qDebug() << deviceModel.getDeviceList().count();
        Device& device = deviceModel.getDeviceList().last();
        TouchButton *button = new TouchButton(deviceModel.getDeviceList().last().ip);
        rootLayout->insertWidget(deviceModel.getDeviceList().count() - 1, button, 0, Qt::AlignCenter);
        connect(button, &QPushButton::clicked, this, [=]() {
            Device dev(device.ip);
            emit onModelClicked(dev);
        });
    });
}

MenuDialog::~MenuDialog() {
    for(int i = 0; i < buttons.count(); i++) {
        delete buttons.at(i);
    }
}

void MenuDialog::initView() {
    QVBoxLayout *rootLayout = reinterpret_cast<QVBoxLayout*>(layout());
    if(rootLayout) {
//        rootLayout->addStretch(1);
        for(int i = 0; i < buttons.count(); i++) {
            rootLayout->addWidget(buttons.at(i), 0, Qt::AlignCenter);
        }
        TouchButton* addButton = new TouchButton("+");
        rootLayout->addWidget(addButton, 0, Qt::AlignCenter);
        rootLayout->addStretch(1);

        connect(addButton, &QPushButton::clicked, this, [=]() {
            QString ip = QInputDialog::getText(NULL,
                                       "设置",
                                       "输入摄像头IP，如: 192.168.1.100",
                                       QLineEdit::Normal);
            qDebug() << ip;
            if(ip.isEmpty()) {
                return;
            }
            Device device(ip);
            deviceModel.addOne(device);
        });
    }
}

void MenuDialog::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
//    QRect rect = this->parentWidget()->geometry();
//    rect.setWidth(this->width());
//    setGeometry(rect);
    move(QPoint(0, 0));
}
