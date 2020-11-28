#ifndef PENSTATE_H
#define PENSTATE_H

#include <QObject>
#include <QWidget>
#include "common.h"
#include "iconbutton.h"


class PenState : public IconButton
{
    Q_OBJECT
public:
    explicit PenState(const QColor& color, const int width, QWidget *parent = nullptr);
    explicit PenState(const QColor& color, QWidget *parent = nullptr);
    explicit PenState(const int width, QWidget *parent = nullptr);
    explicit PenState(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:

private:
    QColor penColor;
    int penWidth;
};

#endif // PENSTATE_H
