#include "myrender.h"

MyRender::MyRender(QWidget *parent) :
    QOpenGLWidget(parent)
{
    QPixmap pixmap(size());
    pixmap.fill(Qt::white);
    m_currentFrame = pixmap.toImage();

}

MyRender::~MyRender()
{
}

void MyRender::onRender(const QImage &pixmap) {
    QMutexLocker lock(&m_pixmapMutex);
    // [TODO] - prevent memory copy
    m_currentFrame = pixmap;
    //    QPixmap pixmap = QPixmap::fromImage(m_currentFrame);
    //    _pixmap = pixmap.scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    update();
}

void MyRender::paintEvent(QPaintEvent *ev)
{
    QOpenGLWidget::paintEvent(ev);

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QRect targetRect(0, 0, width(), height());

    QMutexLocker lock(&m_pixmapMutex);

    QRect srcRect(0, 0, m_currentFrame.width(), m_currentFrame.height());
    painter.drawImage(targetRect, m_currentFrame, srcRect);
}
