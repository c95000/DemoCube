#ifndef TOPBAR_H
#define TOPBAR_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSvgWidget>
#include "widgets/AspectRatioSvgWidget.h"

class TopBar : public QWidget
{
    Q_OBJECT
public:
    explicit TopBar(QWidget *parent = nullptr);

signals:

};

#endif // TOPBAR_H
