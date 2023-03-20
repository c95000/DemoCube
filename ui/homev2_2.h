#ifndef HOMEV2_2_H
#define HOMEV2_2_H

#include <QMainWindow>
#include <QWidget>
#include "ui/CameraViewWidget.h"
#include "ui/MenuDialog.h"

class HomeV2_2 : public QMainWindow
{
    Q_OBJECT
public:
    explicit HomeV2_2(QWidget *parent = nullptr);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
signals:
    void resized();
private:
    MenuDialog* menuDialog;
    QWidget *mainView;
    QWidget *secondView;
    QWidget *thirdView;
    QList<CameraViewWidget*> pages;
    QMap<Device, CameraViewWidget*> pageMap;
};

#endif // HOMEV2_2_H
