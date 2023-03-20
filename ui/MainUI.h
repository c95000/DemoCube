#ifndef MAINUI_H
#define MAINUI_H

#include <QWidget>
#include "ui/CameraViewWidget.h"

class MainUI : public QWidget
{
    Q_OBJECT
public:
    explicit MainUI(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:
    void resized();
private:
    QWidget *mainView;
    QWidget *secondView;
    QWidget *thirdView;
    QList<CameraViewWidget*> pages;
    QWidget* currentPage;
    QMap<Device, CameraViewWidget*> pageMap;
};

#endif // MAINUI_H
