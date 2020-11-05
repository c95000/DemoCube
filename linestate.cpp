#include "linestate.h"
#include "ui_linestate.h"
#include <QPen>
#include <QPainter>
#include <QResizeEvent>
#include "common.h"

LineState::LineState(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineState),
    color(Qt::black),
    width(5)
{
    ui->setupUi(this);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

//    QPalette pal(palette());
//    pal.setColor(QPalette::Background, QColor(255,255,0)); //设置背景黑色
//    setAutoFillBackground(true);
//    setPalette(pal);
}

LineState::~LineState()
{
    delete ui;
}


void LineState::setColor(QColor &color) {
    this->color = color;
    update();
}
void LineState::setWidth(int width) {
    this->width = width;
    update();
}

void LineState::setSize(QResizeEvent *event) {
    QSize size = event->size();
    printf("LineState setSize is called. %d x %d", size.width(), size.height());
}


void LineState::paintEvent(QPaintEvent *event) {
    QPixmap pixmap(size());
    pixmap.fill(Qt::white);

    QPen pen;                                    //新建一个QPen对象
    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setColor(color);                        //设置画笔的颜色
    pen.setWidth(width);

    QPainter painter(this);//将_pixmap作为画布
    painter.setPen(pen);

//    printf("LineState: %d x %d", size().width(), size().height());
    int x = 0;
    int y = (size().height()) / 2;
    painter.drawLine(0, y, size().width(), y);
}
