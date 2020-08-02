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
#include <QOpenGLFunctions>
#include "vlcwrapper.h"

class MyRender : public QOpenGLWidget, public VlcRenderCb, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MyRender(QWidget *parent = nullptr);
    ~MyRender();

    void onRender(const QImage &pixmap) override;

    void copyCurrentImage(QImage& image);
protected:
    void paintEvent(QPaintEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QImage m_currentFrame;
    QMutex m_pixmapMutex;
};

#endif // MYRENDER_H
