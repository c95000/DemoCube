#ifndef VIDEOGLRENDER_H
#define VIDEOGLRENDER_H

#include <QWidget>
#include <QtOpenGL>
#include "utils/ThemeUtils.h"

class VideoGLRender : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit VideoGLRender(QWidget *parent = nullptr);

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;
signals:

};

#endif // VIDEOGLRENDER_H
