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

protected:
    void resizeEvent(QResizeEvent *event);

public:

    const QPushButton *insertButton();

    const QPushButton *commentButton();

    const QPushButton *takePictureButton();

    const QPushButton *takeVideoButton();

    const QPushButton *playPauseButton();

    const QPushButton *settingButton();

private slots:
    void onSettingButtonClicked();

private:
    Ui::ToolBar *ui;


};

#endif // TOOLBAR_H
