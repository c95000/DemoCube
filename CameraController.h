#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QWidget>

namespace Ui {
class CameraController;
}

class CameraController : public QWidget
{
    Q_OBJECT

public:
    explicit CameraController(QWidget *parent = nullptr);
    ~CameraController();

signals:
    void zoomTele();
    void zoomWide();

private slots:
    void onZoomTeleClicked();
    void onZoomWideClicked();

private:
    Ui::CameraController *ui;
};

#endif // CAMERACONTROLLER_H
