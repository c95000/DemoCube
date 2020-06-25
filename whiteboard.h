#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QWidget>

class WhiteBoard : public QWidget
{
    Q_OBJECT

public:
    explicit WhiteBoard(QWidget *parent = nullptr);
    ~WhiteBoard();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void moveEvent(QMoveEvent *event);

private:
};

#endif // WHITEBOARD_H
