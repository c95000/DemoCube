#include "TouchButton.h"

TouchButton::TouchButton(QWidget *parent)
    : QPushButton{parent}
{
    initView();
}

TouchButton::TouchButton(const QString &text, QWidget *parent)
    : QPushButton{text, parent}
{
    initView();
}

void TouchButton::initView() {
    setFixedSize(80, 80);
}
