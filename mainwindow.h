#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vlc/vlc.h"
#include "RenderWidget.h"
#include "whiteboard.h"
#include "mypaint.h"
#include <QTimer>
#include "vlcwrapper.h"
#include "CameraController.h"
#include "mp4encoder.h"
#include "recordlabel.h"
#include "jyplayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_btnNotaion_clicked();

    void on_takePicture();

    void on_start_RecordVideo();

    void on_stop_RecordVideo();

    void onRecordStarted();

    void on_btnCaptureVideo_clicked();

    void on_btnCapturePanel_clicked();

    void on_btnPlayRtsp_clicked();

    void on_btnSaveNotaion_clicked();

    void on_timeout();

    void on_btnStop_clicked();

    void on_btnPlay2_clicked();

    void on_btnPause_clicked();

    void on_btnPlayLocal_clicked();

    void on_btnPlayPause_clicked();

    void on_btnComment_clicked();

    void on_btnComment_quit();

    void on_btnDevice_clicked();

    void onPlayerStarted();
    void onPlayerStopped();
    void onPlayerPaused();
    void onPlayerError(QString& err);

    void onSelectedRtsp(QString& rtspUrl);

    void onZoomTele();
    void onZoomWide();

    void onScreenChanged();
private:


    void allocVideoBuf(int width, int height);
    char* getVideoBuf() const;

    void showNotation(QPixmap& pixmap);

    void saveNotation(QPixmap& pixmap);

    void showWhiteBoard(bool state);

    bool isCommenting();

private:
    Ui::MainWindow *ui;

    MyPaint* myPaint = NULL;

    QTimer* timerClock = NULL;

    VlcWrapper* vlcWrapper = NULL;
    JyPlayer *m_player = NULL;

    CameraController* cameraController;

    RecordLabel* recordLabel;
};
#endif // MAINWINDOW_H
