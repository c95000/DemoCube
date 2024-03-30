#include "MainUI.h"
#include "utils/ThemeUtils.h"
#include "ui/TestViewController.h"
#include <QVBoxLayout>
#include <QDebug>
#include "ui/MenuDialog.h"
#include "ui/homev2_2.h"

MainUI::MainUI(QWidget *parent)
    : QMainWindow{parent}
{
    ThemeUtils::setBackground(this, 0xeeeeee);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    QWidget* mainPage = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    mainPage->setLayout(layout);
//    ThemeUtils::setBackground(stackedWidget, 0xeeee00);

//    TestViewController* testViewController = new TestViewController(this);
//    rootLayout->addWidget(testViewController, 0, Qt::AlignCenter);

//    MenuDialog* menuDialog = new MenuDialog(this);
//    menuDialog->hide();
//    connect(testViewController, &TestViewController::onFuncButton1Clicked, this, [=]() {
//        qDebug() << "testViewController onFuncButton1Clicked";
//        menuDialog->show();
//    });

//    connect(this, &MainUI::resized, menuDialog, [=]() {
//        qDebug() << this->geometry();
//        menuDialog->resize(QSize(this->width()/4, this->height()));
//    });

//    connect(menuDialog, &MenuDialog::onModelClicked, this, [=](Device& device) {
//        qDebug() << device.getUrl();
//        if(!pageMap[device]) {
//            pageMap.insert(device, new CameraViewWidget(device, this));
//        }
//        rootLayout->takeAt(0);
//        rootLayout->addWidget(pageMap[device]);
//        qDebug() << "pageMap.count: " << pageMap.count();
//        qDebug() << "rootLayout->children().count(): " << rootLayout->children().count();
//        menuDialog->raise();
//    });

    // 创建三个按钮并添加到布局中
    QPushButton *button1 = new QPushButton("Button 1");
    QPushButton *button2 = new QPushButton("Button 2");
    QPushButton *button3 = new QPushButton("Button 3");
    // 连接按钮的 clicked 信号到槽函数
    connect(button1, &QPushButton::clicked, this, &MainUI::onButton1Clicked);
    // 连接按钮的 clicked 信号到槽函数
    connect(button2, &QPushButton::clicked, this, &MainUI::onButton2Clicked);
    // 连接按钮的 clicked 信号到槽函数
    connect(button3, &QPushButton::clicked, this, &MainUI::onButton3Clicked);

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);

    stackedWidget->addWidget(mainPage);


    // 创建内容小部件
    QWidget *content1 = new HomeV2_2();
    QWidget *content2 = new QLabel("content2");
    QWidget *content3 = new QLabel("content3");
    stackedWidget->addWidget(content1);
    stackedWidget->addWidget(content2);
    stackedWidget->addWidget(content3);
}

void MainUI::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    emit resized();
}

void MainUI::closeEvent(QCloseEvent *event) {
    if(stackedWidget->currentIndex() == 0) {
        // 如果已经是主页，接受关闭事件，应用将退出
        event->accept();
    } else {
        stackedWidget->setCurrentIndex(0);
        // 忽略关闭事件，这样应用不会退出
        event->ignore();
    }
}

void MainUI::onButton1Clicked() {
    stackedWidget->setCurrentIndex(1); // 显示第一个内容
//    QSize currentSize = this->size(); // 获取当前窗口的大小
//    QPoint currentPos = this->pos(); // 获取当前窗口的位置
//    // 创建新页面的实例并显示
//    HomeV2_2 *newPage = new HomeV2_2();
//    newPage->resize(currentSize);
//    newPage->move(currentPos);
//    connect(newPage, &HomeV2_2::closed, this, [=](){
//        qDebug() << "HomeV2_2::closed";
//        this->show();
//    });
//    newPage->show();
//    this->hide();
}
void MainUI::onButton2Clicked() {
    stackedWidget->setCurrentIndex(2);
}
void MainUI::onButton3Clicked() {
    stackedWidget->setCurrentIndex(3);
}
