#ifndef MEDIACONTROLLER_H
#define MEDIACONTROLLER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class MediaController;
}

class MediaController : public QWidget
{
    Q_OBJECT

public:
    explicit MediaController(QWidget *parent = nullptr);
    ~MediaController();

    const QLabel * timeLable();
    const QPushButton *playPauseButton();
    const QPushButton *stopButton();
private:
    Ui::MediaController *ui;
};

#endif // MEDIACONTROLLER_H
