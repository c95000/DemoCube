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
    explicit PenStyle(const QColor& color, const int width, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:
    void onPenChanged(int rgb, int width);

public:
    QColor getColor() const;
    int getWidth() const;

private:
    QColor lineColor;
    int lineWidth;
};

#endif // PENSTYLE_H
