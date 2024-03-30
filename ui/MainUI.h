#ifndef MAINUI_H
#define MAINUI_H

#include <QWidget>
#include <QMainWindow>
#include "ui/CameraViewWidget.h"

class MainUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainUI(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override; // 重写 closeEvent

signals:
    void resized();

private slots:
    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();

private:
    QWidget *mainView;
    QWidget *secondView;
    QWidget *thirdView;
    QList<CameraViewWidget*> pages;
    QWidget* currentPage;
    QMap<Device, CameraViewWidget*> pageMap;

    QStackedWidget *stackedWidget;
};

#endif // MAINUI_H
