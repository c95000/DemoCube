#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QWidget>

class WhiteBoard : public QWidget
{
    Q_OBJECT

public:
    explicit WhiteBoard(QWidget *parent = nullptr);
    ~WhiteBoard();

private:
};

#endif // WHITEBOARD_H
