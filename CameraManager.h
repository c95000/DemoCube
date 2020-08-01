#ifndef CAMCERAMANAGER_H
#define CAMCERAMANAGER_H

#include <QWidget>

namespace Ui {
class CameraManager;
}

class CameraManager : public QWidget
{
    Q_OBJECT

public:
    explicit CameraManager(QWidget *parent = nullptr);
    ~CameraManager();

private slots:
    void onVideoSetting1_Clicked();
    void onVideoSetting2_Clicked();
    void onVideoSetting3_Clicked();

private:
    void setCameraUrl(int index);

private:
    Ui::CameraManager *ui;
};

#endif // CAMCERAMANAGER_H
