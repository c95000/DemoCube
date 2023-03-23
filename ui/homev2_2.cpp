#include "homev2_2.h"
#include "utils/ThemeUtils.h"
#include "ui/TestViewController.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QMouseEvent>

HomeV2_2::HomeV2_2(QWidget *parent)
    : QMainWindow{parent}
{
    ThemeUtils::setBackground(this, 0xeeeeee);

    mainView = new QWidget();
//    secondView = new QWidget();
//    thirdView = new QWidget();
//    ThemeUtils::setBackground(secondView, 0xffff00);
//    ThemeUtils::setBackground(thirdView, 0xff0000);
    setCentralWidget(mainView);

//    QHBoxLayout* rootLayout = new QHBoxLayout;
//    mainView->setLayout(rootLayout);

    TestViewController* testViewController = new TestViewController();
//    rootLayout->addWidget(testViewController, 0, Qt::AlignCenter);

    menuDialog = new MenuDialog(this);
    menuDialog->hide();
    connect(testViewController, &TestViewController::onFuncButton1Clicked, this, [=]() {
        qDebug() << "testViewController onFuncButton1Clicked";
        menuDialog->show();
    });

    connect(this, &HomeV2_2::resized, menuDialog, [=]() {
        qDebug() << this->geometry();
        menuDialog->resize(QSize(this->width()/4, this->height()));
    });

    connect(menuDialog, &MenuDialog::onModelClicked, this, [=](Device& device) {
        if(!pageMap[device]) {
            pageMap.insert(device, new CameraViewWidget(device) );
        }
        if(this->centralWidget() != pageMap[device]) {
            takeCentralWidget();
            setCentralWidget(pageMap[device]);
        } else {
            qDebug() << "same centralWidget";
        }

        qDebug() << "pageMap.count: " << pageMap.count();
        menuDialog->raise();
    });
}

void HomeV2_2::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    emit resized();
}

void HomeV2_2::mousePressEvent(QMouseEvent *event) {
    QMainWindow::mousePressEvent(event);
    qDebug() << tr("(%1,%2)").arg(event->x()).arg(event->y());
    if(event->x() < width() / 4) {
        menuDialog->show();
        qDebug() << menuDialog->isHidden();
    } else {
        menuDialog->hide();
        qDebug() << menuDialog->isHidden();
    }
}

