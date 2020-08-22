#include "HTitleButton.h"
#include "ui_HTitleButton.h"
#include <QTimer>
#include <QEvent>
#include "common.h"

HTitleButton::HTitleButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HTitleButton)
{
    ui->setupUi(this);
    setStyleSheet("color:white;");
    ui->label->setContentsMargins(5, 0, 20, 0);
}

HTitleButton::~HTitleButton()
{
    delete ui;
}

bool HTitleButton::event(QEvent* event)
{
    if(event->type() == QEvent::MouseButtonDblClick) {
        emit doubleClicked();
        return true;
    }
    return QWidget::event(event);
}

void HTitleButton::enterEvent(QEvent *event) {
    QPalette pal(palette());
    QColor bg = pal.window().color();
    bg.setAlpha(60);
    pal.setColor(QPalette::Background, bg);
    setAutoFillBackground(true);
    setPalette(pal);
}

void HTitleButton::leaveEvent(QEvent *event) {
    QPalette pal(palette());
    QColor bg = pal.window().color();
    bg.setAlpha(0);
    pal.setColor(QPalette::Background, bg);
    setAutoFillBackground(true);
    setPalette(pal);
}

void HTitleButton::setText(const QString &text) {
    ui->label->setText(text);
}


ImageButton *HTitleButton::imageButton() {
    return ui->button;
}

QPushButton *HTitleButton::button() {
    return ui->button;
}
