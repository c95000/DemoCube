#ifndef MYRENDER_H
#define MYRENDER_H
#include <QOpenGLWidget>
#include <QMutex>
#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QToolBar>
#include <QAction>
#include <QPalette>
#include <QColor>
#include <QMenu>
#include <QFileDialog>
#include <QTextEdit>
#include <QLabel>
#include "vlcwrapper.h"

class MyRender : public QOpenGLWidget, public VlcRenderCb
{
    Q_OBJECT

public:
    explicit MyRender(QWidget *parent = nullptr);
    ~MyRender();

    void onRender(const QImage &pixmap) override;

    void copyCurrentImage(QImage& image);
protected:
    void paintEvent(QPaintEvent *);//重写窗体重绘事件
    virtual QSize sizeHint () const;

private:
    QImage m_currentFrame;
    QMutex m_pixmapMutex;
};

#endif // MYRENDER_H
