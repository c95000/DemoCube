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

signals:
    void selectedRtsp(QString& rtspUrl);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void onSettingClicked();
    void onDoubleClicked();

private:
    void setCameraUrl(int index);

private:
    Ui::CameraManager *ui;
    QList<QString> *urlList;
};

#endif // CAMCERAMANAGER_H
