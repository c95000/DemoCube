#include "myrender.h"
#include <QDebug>
#define printf qDebug
MyRender::MyRender(QWidget *parent) :
    QOpenGLWidget(parent)
{
//    QPixmap pixmap(size());
//    pixmap.fill(Qt::black);
//    m_currentFrame = pixmap.toImage();
//    sizePolicy().setHeightForWidth(true);
//    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    printf("MyRender width:%d height:%d", size().width(), size().height());
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
    printf("paintEvent width:%d height:%d", size().width(), size().height());
    QOpenGLWidget::paintEvent(ev);

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QRect targetRect(0, 0, width(), height());

    QMutexLocker lock(&m_pixmapMutex);

    QRect srcRect(0, 0, m_currentFrame.width(), m_currentFrame.height());
    painter.drawImage(targetRect, m_currentFrame, srcRect);
}

QSize MyRender::sizeHint() const
{
    int width = size().width();
    int height = size().height();
    printf("old width:%d height:%d", width, height);

//    if(width > height * 4 / 3)
//    {
//        width = height * 4 / 3;
//    }
//    else
//    {
//        height = width * 3 / 4;
//    }

//    printf("new width:%d height:%d", width, height);
//    return QSize(width, height);
    return size();
}

void MyRender::resizeEvent(QResizeEvent *e) {

}

