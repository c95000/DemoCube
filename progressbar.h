#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>
#include "common.h"
#include <QLabel>
#include <QSlider>

class ProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressBar(QWidget *parent = nullptr);
    virtual ~ProgressBar();


    int value() const;
    void reset();
protected:
    virtual void resizeEvent(QResizeEvent *event);

public Q_SLOTS:
    void setValue(int value, int maximum);

Q_SIGNALS:
    void valueChanged(int value);

private:
    QLabel *left;
    QSlider *slider;
    QLabel *right;
};

#endif // PROGRESSBAR_H
