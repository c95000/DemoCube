#ifndef CAMERAPREVIEW_H
#define CAMERAPREVIEW_H

#include <QWidget>

class CameraPreview : public QWidget
{
    Q_OBJECT
public:
    explicit CameraPreview(QString& src, QWidget *parent = nullptr);

signals:

private:
    QString& src;
};

#endif // CAMERAPREVIEW_H
