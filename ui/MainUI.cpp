#include "MainUI.h"
#include "utils/ThemeUtils.h"
#include "ui/TestViewController.h"
#include <QHBoxLayout>
#include <QDebug>
#include "ui/MenuDialog.h"

MainUI::MainUI(QWidget *parent)
    : QWidget{parent}
{
    ThemeUtils::setBackground(this, 0xeeeeee);

    QHBoxLayout* rootLayout = new QHBoxLayout;
    setLayout(rootLayout);

    TestViewController* testViewController = new TestViewController(this);
    rootLayout->addWidget(testViewController, 0, Qt::AlignCenter);

    MenuDialog* menuDialog = new MenuDialog(this);
    menuDialog->hide();
    connect(testViewController, &TestViewController::onFuncButton1Clicked, this, [=]() {
        qDebug() << "testViewController onFuncButton1Clicked";
        menuDialog->show();
    });

    connect(this, &MainUI::resized, menuDialog, [=]() {
        qDebug() << this->geometry();
        menuDialog->resize(QSize(this->width()/4, this->height()));
    });

    connect(menuDialog, &MenuDialog::onModelClicked, this, [=](Device& device) {
        qDebug() << device.getUrl();
        if(!pageMap[device]) {
            pageMap.insert(device, new CameraViewWidget(device, this));
        }
        rootLayout->takeAt(0);
        rootLayout->addWidget(pageMap[device]);
        qDebug() << "pageMap.count: " << pageMap.count();
        qDebug() << "rootLayout->children().count(): " << rootLayout->children().count();
        menuDialog->raise();
    });
}

void MainUI::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    emit resized();
}
