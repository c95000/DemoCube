#include "whiteboard.h"

WhiteBoard::WhiteBoard(QWidget *parent) :
    QWidget(parent)
{
    setMouseTracking(true);//开启鼠标实时追踪，监听鼠标移动事件，默认只有按下时才监听

    //设置背景黑色
         //方法一
    //     QPalette palt(this->palette());
    //     palt.setColor(QPalette::Background, Qt::white);
    //     this->setAutoFillBackground(true);
    //     this->setPalette(palt);
         //方法二
    this->setStyleSheet("background-color:white;");
}

WhiteBoard::~WhiteBoard()
{
}

void WhiteBoard::mousePressEvent(QMouseEvent *event) {
    //this->mousePressEvent(event);
}
void WhiteBoard::mouseReleaseEvent(QMouseEvent *event) {

}
void WhiteBoard::mouseMoveEvent(QMouseEvent *event) {

}
void WhiteBoard::keyPressEvent(QKeyEvent *event) {

}
void WhiteBoard::paintEvent(QPaintEvent *event) {

}
void WhiteBoard::moveEvent(QMoveEvent *event) {

}
