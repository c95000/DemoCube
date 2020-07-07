#include "RenderWidget.h"

#include <QPainter>
#include <QPaintEvent>

CRenderWidget::CRenderWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{}

void CRenderWidget::setPixmap(const QImage &p)
{
    QMutexLocker lock(&m_pixmapMutex);
    // [TODO] - prevent memory copy
    m_currentFrame = p;
    update();
}

void CRenderWidget::getCurrentPixmap(QImage &p)
{
    QMutexLocker lock(&m_pixmapMutex);
    // [TODO] - prevent memory copy
    p = m_currentFrame;
}

void CRenderWidget::onRender(const QImage &pixmap) {
    QMutexLocker lock(&m_pixmapMutex);
    // [TODO] - prevent memory copy
    m_currentFrame = pixmap;
    update();
}

void CRenderWidget::paintEvent(QPaintEvent *ev)
{
    QOpenGLWidget::paintEvent(ev);

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QRect targetRect(0, 0, width(), height());

    QMutexLocker lock(&m_pixmapMutex);

    QRect srcRect(0, 0, m_currentFrame.width(), m_currentFrame.height());
    painter.drawImage(targetRect, m_currentFrame, srcRect);

    //QPixmap _pixmap = QPixmap(size());//新建pixmap
    //_pixmap.fill(Qt::white);//背景色填充为白色
    //painter.drawPixmap(0,0, _pixmap);//将pixmap画到窗体
}
