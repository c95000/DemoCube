#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vlc/vlc.h"
#include "RenderWidget.h"
#include "whiteboard.h"
#include "mypaint.h"
#include <QTimer>
#include "vlcwrapper.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnPlay_clicked();

    void on_btnNotaion_clicked();

    void on_btnCaptureScreen_clicked();

    void on_btnCaptureVideo_clicked();

    void on_btnCapturePanel_clicked();

    void on_btnPlayRtsp_clicked();

    void on_btnSaveNotaion_clicked();

    void on_timeout();

    void on_btnStop_clicked();

    void on_btnPlay2_clicked();

    void on_btnPause_clicked();

    void on_btnWhiteBoard_clicked();

private:


    void allocVideoBuf(int width, int height);
    char* getVideoBuf() const;

    void showNotation(QPixmap& pixmap);

    void saveNotation(QPixmap& pixmap);

private:
    Ui::MainWindow *ui;

    MyPaint* myPaint;
    MyPaint* myNotation;

    QTimer* timerClock;

    VlcWrapper* vlcWrapper;
};
#endif // MAINWINDOW_H
