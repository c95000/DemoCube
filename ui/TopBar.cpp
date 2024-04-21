#include "TopBar.h"

TopBar::TopBar(QWidget *parent)
    : QWidget{parent}
{
    // 设置自动填充背景，确保背景样式可见
    setAutoFillBackground(true);

    // 创建垂直布局
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 添加子控件
    QPushButton *button1 = new QPushButton("Button 1");
    QPushButton *button2 = new QPushButton("Button 2");

    QSvgWidget *svgWidget = new QSvgWidget(":/res/icons/upward_selected_icon.svg");
    svgWidget->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
    // 设置窗口大小
    svgWidget->setFixedSize(300, 300);
    AspectRatioSvgWidget *aspectRatioWidget = new AspectRatioSvgWidget(":/res/icons/stop.svg", this);

    // 将按钮添加到布局中
//    layout->addWidget(button1);
//    layout->addWidget(button2);
    layout->addWidget(svgWidget);
//    layout->addWidget(aspectRatioWidget);

    // 设置布局到当前控件
    setLayout(layout);

    // 应用样式
//    setStyleSheet(
//                "TopBar {"
//                "  background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
//                "    stop:0 #0A1729, stop:0.5 #082239, stop:1 #082B41);"
//                "}"
//                );

    // 布局设置，确保宽度自适应父窗口，高度根据内容调整
    layout->setAlignment(Qt::AlignTop);
}
