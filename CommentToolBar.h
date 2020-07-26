#ifndef COMMENTTOOLBAR_H
#define COMMENTTOOLBAR_H

#include <QWidget>
#include <QPushButton>
#include "ImageButton.h"

namespace Ui {
class CommentToolBar;
}

class CommentToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit CommentToolBar(QWidget *parent = nullptr);
    ~CommentToolBar();

//    const QPushButton *closeButton();
//    const QPushButton *redPenButton();
//    const QPushButton *whitePenButton();
//    const QPushButton *blackPenButton();
//    const QPushButton *rubberButton();

private:
    Ui::CommentToolBar *ui;

    ImageButton* closeButton;
    ImageButton* rubberButton;
    ImageButton* whiteBoardButton;
//    ImageButton* closeButton;
};

#endif // COMMENTTOOLBAR_H
