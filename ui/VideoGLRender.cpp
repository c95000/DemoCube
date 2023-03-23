#include "VideoGLRender.h"

VideoGLRender::VideoGLRender(QWidget *parent)
    : QOpenGLWidget{parent}
{
//    ThemeUtils::setBackground(this, 0xFF00FF, 0.5);
}


void VideoGLRender::initializeGL() {
    initializeOpenGLFunctions();
}
void VideoGLRender::paintGL() {
    glClearColor(170.0/255, 170.0/255, 170.0/255, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void VideoGLRender::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}
