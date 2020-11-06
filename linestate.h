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

    void setLineColor(QColor &color);
    void setLineWidth(int width);

public slots:
    void setSize(QResizeEvent *event);

protected:
    virtual void paintEvent(QPaintEvent *event);
//    virtual void resizeEvent(QResizeEvent *event);
private:
    Ui::LineState *ui;

    QColor lineColor;
    int lineWidth;
};

#endif // LINESTATE_H
