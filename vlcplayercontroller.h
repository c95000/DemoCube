#ifndef VLCPLAYERCONTROLLER_H
#define VLCPLAYERCONTROLLER_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class VlcPlayerController;
}

class VlcPlayerController : public QWidget
{
    Q_OBJECT

public:
    explicit VlcPlayerController(QWidget *parent = nullptr);
    ~VlcPlayerController();

signals:
    void play();
    void pause();
    void stop();
    void close();
    void takePicture();
    void comment();

public slots:
    void onPlay();
    void onPause();

private:
    Ui::VlcPlayerController *ui;

    QPushButton *btnPlay;
    QPushButton *btnPause;
    QPushButton *btnStop;
    QPushButton *btnTakePicture;
    QPushButton *btnComment;
    QPushButton *btnExit;
};

#endif // VLCPLAYERCONTROLLER_H
