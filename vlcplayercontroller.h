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
private:
    Ui::VlcPlayerController *ui;

    QPushButton *btnOpen;
    QPushButton *btnPlay;
    QPushButton *btnPause;
    QPushButton *btnStop;
    QPushButton *btnTakePicture;
    QPushButton *btnComment;
    QPushButton *btnExit;
};

#endif // VLCPLAYERCONTROLLER_H
