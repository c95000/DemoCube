#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QStack>
#include <QDebug>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView(QWidget *parent = nullptr);
    void setBackgroundImage(const QPixmap &pixmap);
    void setPenColor(const QColor &color);
    void setPenWidth(int width);
    void undo();
signals:

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QGraphicsScene *scene;
    QStack<QGraphicsItem*> historyStack;
    QPen pen;
    QPointF lastPoint;
    bool drawing = false;
};

#endif // MYGRAPHICSVIEW_H
