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
protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::CommentToolBar *ui;
};

#endif // COMMENTTOOLBAR_H
