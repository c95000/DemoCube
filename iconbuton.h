#ifndef ICONBUTON_H
#define ICONBUTON_H

#include <QObject>
#include <QWidget>
#include "common.h"
#include <QPushButton>
#include <QToolButton>

class IconButon : public QToolButton
{
    Q_OBJECT
public:
    explicit IconButon(const QString& icon, const QString& activeIcon, QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *) override;

signals:

};

#endif // ICONBUTON_H
