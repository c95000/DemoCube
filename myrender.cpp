#include "myrender.h"
#include "common.h"
#include "GL/glu.h"

MyRender::MyRender(QWidget *parent) :
    QOpenGLWidget(parent)
{
//    QPixmap pixmap(size());
//    pixmap.fill(Qt::black);
//    m_currentFrame = pixmap.toImage();
//    sizePolicy().setHeightForWidth(true);
//    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    //设置背景黑色
    //方法一
//    QPalette palt(palette());
//    palt.setColor(QPalette::Background, QColor(180, 180, 180));
//    this->setAutoFillBackground(true);
//    this->setPalette(palt);

    //方法二
//    this->setStyleSheet("background-color:yellow;");
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

void MyRender::copyCurrentImage(QImage& image) {
    QMutexLocker lock(&m_pixmapMutex);
    image = m_currentFrame.copy();
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

void MyRender::initializeGL() {
    //调用内容初始化函数
    initializeOpenGLFunctions();
}

void MyRender::resizeGL(int w, int h) {
    //当窗口大小改变时，调整界面坐标显示高度和宽度
    glViewport(0, 0, w, h);
}

void MyRender::paintGL() {
    //QOpenGLWidget::paintGL();
    //清除之前图形并将背景设置为黑色（设置为黑色纯粹个人爱好！）
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.6f, 0.6f, 0.6f, 0.0f);
}



