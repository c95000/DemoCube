#ifndef COMMENTTOOLBAR_H
#define COMMENTTOOLBAR_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class CommentToolBar;
}

enum CommentToolBarEvent {
    Close,
    Redpen,
    Whitepen,
    Blackpen,
    Rubber,
};

class CommentToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit CommentToolBar(QWidget *parent = nullptr);
    ~CommentToolBar();

    const QPushButton *closeButton();
    const QPushButton *redPenButton();
    const QPushButton *whitePenButton();
    const QPushButton *blackPenButton();
    const QPushButton *rubberButton();

Q_SIGNALS:
    void signalOfEvent(CommentToolBarEvent event);
    void test();

public Q_SLOTS:
    void slotOfClose();
    void slotOfRedpen();
    void slotOfBlackpen();
    void slotOfWhitepen();
    void slotOfRubber();


private:
    Ui::CommentToolBar *ui;
};

#endif // COMMENTTOOLBAR_H
