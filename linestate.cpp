#include "linestate.h"
#include "ui_linestate.h"
#include <QPen>
#include <QPainter>
#include <QResizeEvent>
#include "common.h"

LineState::LineState(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineState),
    lineColor(Qt::black),
    lineWidth(5)
{
    ui->setupUi(this);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

//    QPalette pal(palette());
//    pal.setColor(QPalette::Background, QColor(255,255,0)); //设置背景黑色
//    setAutoFillBackground(true);
//    setPalette(pal);
    setStyleSheet("#frame{border:2px solid #014F84}#background-color:#00d8ff");
}

LineState::~LineState()
{
    delete ui;
}


void LineState::setLineColor(QColor &color) {
    this->lineColor = color;
    update();
}
void LineState::setLineWidth(int width) {
    this->lineWidth = width;
    update();
}

void LineState::setSize(QResizeEvent *event) {
    QSize size = event->size();
    printf("LineState setSize is called. %d x %d", size.width(), size.height());
}


void LineState::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.setPen(QColor(200, 200, 200));
    // 上面画线
    painter.drawLine(0, 0, this->width() - 1, 0);
    // 左面画线
    painter.drawLine(0, 0, 0, this->height() - 1);
    // 右侧画线
    painter.drawLine(width() - 1, 0, width() - 1, this->height() - 1);
    // 下面画线
    painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);

    QPen pen;                                    //新建一个QPen对象
    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setColor(lineColor);                        //设置画笔的颜色
    pen.setWidth(lineWidth);


    painter.setPen(pen);

//    printf("LineState: %d x %d", size().width(), size().height());
    int x = 8;
    int y = (size().height()) / 2;
    painter.drawLine(x, y, size().width() - x, y);
}
