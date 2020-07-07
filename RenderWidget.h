#ifndef RenderWidget_h__
#define RenderWidget_h__

#include <QOpenGLWidget>
#include <QMutex>
#include "vlcwrapper.h"

class CRenderWidget : public QOpenGLWidget, public VlcRenderCb
{
    Q_OBJECT
public:
    CRenderWidget(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent *ev);
    virtual void setPixmap(const QImage &pixmap);
    virtual void getCurrentPixmap(QImage &p);

    void onRender(const QImage &pixmap) override;
protected:
    QImage m_currentFrame;
    QMutex m_pixmapMutex;
};
#endif // RenderWidget_h__
