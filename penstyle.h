#ifndef PENSTYLE_H
#define PENSTYLE_H

#include <QObject>
#include <QWidget>
#include "iconbutton.h"
#include "common.h"

class PenStyle : public IconButton
{
    Q_OBJECT
public:
    explicit PenStyle(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:

private:
    QColor lineColor;
    int lineWidth;
};

#endif // PENSTYLE_H
