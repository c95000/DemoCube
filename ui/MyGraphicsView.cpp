#include "MyGraphicsView.h"
#include <QGraphicsItem>

MyGraphicsView::MyGraphicsView(QWidget *parent)
    : QGraphicsView{parent}
{
    scene = new QGraphicsScene(this);
    this->setScene(scene);
    // 可选: 设置一个初始场景大小
    scene->setSceneRect(0, 0, width(), height());
    pen.setColor(Qt::black); // 默认黑色
    pen.setWidth(3); // 默认宽度
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = mapToScene(event->pos());
        drawing = true;
    }
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPointF currentPoint = mapToScene(event->pos());
        QGraphicsLineItem *line = scene->addLine(QLineF(lastPoint, currentPoint), pen);
        historyStack.push(line);
        lastPoint = currentPoint;
    }
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
    }
}

void MyGraphicsView::resizeEvent(QResizeEvent *event) {
    qDebug() << event->size();
    // 当视图大小改变时，更新场景的大小以匹配视图的新大小
    if (scene) {
        QRectF newRect = QRectF(QPointF(0, 0), event->size());
        scene->setSceneRect(newRect);
    }
    QGraphicsView::resizeEvent(event); // 调用基类实现
}

void MyGraphicsView::setBackgroundImage(const QPixmap &pixmap)
{
    scene->clear(); // 如果需要清除旧的内容
    scene->addPixmap(pixmap);
    scene->setSceneRect(pixmap.rect()); // 调整场景的大小以匹配图片
}

void MyGraphicsView::undo()
{
    if (!historyStack.isEmpty()) {
        QGraphicsItem* item = historyStack.pop();
        scene->removeItem(item); // 移除最后一个图形项
        delete item; // 释放资源
    }
}

void MyGraphicsView::setPenColor(const QColor &color)
{
    pen.setColor(color);
}

void MyGraphicsView::setPenWidth(int width)
{
    pen.setWidth(width);
}


