#ifndef LINESTATE_H
#define LINESTATE_H

#include <QWidget>

namespace Ui {
class LineState;
}

class LineState : public QWidget
{
    Q_OBJECT

public:
    explicit LineState(QWidget *parent = nullptr);
    ~LineState();

    void setColor(QColor &color);
    void setWidth(int width);

public slots:
    void setSize(QResizeEvent *event);

protected:
    virtual void paintEvent(QPaintEvent *event);
//    virtual void resizeEvent(QResizeEvent *event);
private:
    Ui::LineState *ui;

    QColor color;
    int width;
};

#endif // LINESTATE_H
