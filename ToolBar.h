#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class ToolBar;
}

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar();

public:

    const QPushButton *insertButton();

    const QPushButton *commentButton();

    const QPushButton *takePictureButton();

    const QPushButton *takeVideoButton();

    const QPushButton *playPauseButton();

    const QPushButton *settingButton();

private:
    Ui::ToolBar *ui;
};

#endif // TOOLBAR_H
