#ifndef VLCPLAYERCONTROLLER_H
#define VLCPLAYERCONTROLLER_H

#include <QWidget>
#include <QPushButton>
#include "progressbar.h"

namespace Ui {
class VlcPlayerController;
}

class VlcPlayerController : public QWidget
{
    Q_OBJECT

public:
    explicit VlcPlayerController(QWidget *parent = nullptr);
    ~VlcPlayerController();

protected:
    void resizeEvent(QResizeEvent *event);

signals:
    void play(const QString& fileName);
    void play();
    void pause();
    void stop();
    void close();
    void takePicture();
    void comment();

public slots:
    void onOpen();
    void onPlay();
    void onPause();

    void played();
    void paused();
    void stopped();

    void updateProgress(int current, int total);
private:
    Ui::VlcPlayerController *ui;

    QPushButton *btnOpen;
    QPushButton *btnPlay;
    QPushButton *btnPause;
    QPushButton *btnStop;
    QPushButton *btnTakePicture;
    QPushButton *btnComment;
    QPushButton *btnExit;

    ProgressBar *progressBar;
};

#endif // VLCPLAYERCONTROLLER_H
