#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QObject>
#include <QWidget>

class CameraView : public QWidget
{
    Q_OBJECT
public:
    explicit CameraView(QWidget *parent = nullptr);
    ~CameraView();

signals:
public slots:
    void onConnect(const QString& sourceUrl);
    void onDisconnect();

};

#endif // CAMERAVIEW_H
