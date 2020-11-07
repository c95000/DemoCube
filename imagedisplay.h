#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include <QWidget>
#include "common.h"
#include "vlc/vlc.h"

namespace Ui {
class ImageDisplay;
}

class ImageDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit ImageDisplay(QWidget *parent = nullptr);
    ~ImageDisplay();

private slots:
    void onBtnOpen();
    void onBtnNext();
    void onBtnPlay();

private:
    Ui::ImageDisplay *ui;
    QLabel *imageView;

    libvlc_instance_t *m_vlcInstance;
    libvlc_media_player_t *m_vlcPlayer;
};

#endif // IMAGEDISPLAY_H
