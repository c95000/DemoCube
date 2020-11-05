#ifndef FREEDRAWING_H
#define FREEDRAWING_H

#include <QWidget>

class Line : public QObject{
    Q_OBJECT

public:
    explicit Line();

    void append(QPoint& point) {
        _lines.append(point);
    }

private:
    QVector<QPoint> _lines;
};


namespace Ui {
class FreeDrawing;
}

class FreeDrawing : public QWidget
{
    Q_OBJECT

public:
    explicit FreeDrawing(QWidget *parent = nullptr);
    explicit FreeDrawing(const QString& imageSource, QWidget *parent = nullptr);
    ~FreeDrawing();

protected:
    void paintEvent(QPaintEvent *);//重写窗体重绘事件
    void mousePressEvent(QMouseEvent *);//重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *);//重写鼠标释放事件
    void mouseMoveEvent(QMouseEvent *);//重写鼠标移动事件
    void resizeEvent(QResizeEvent *event);

private:
    Ui::FreeDrawing *ui;

    QPixmap _originPixmap;
    QPixmap _pixmap;
    QVector<QVector<QPoint> > _lines;//线条集合(一条线条可包含多个线段)
};

#endif // FREEDRAWING_H
