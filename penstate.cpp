#include "penstate.h"

PenState::PenState(const QColor& color, const int width, QWidget *parent) : IconButton(parent), penColor(color), penWidth(width)
{
//    connect(this, &QPushButton::clicked, [=](){
//        printf("clicked");
//        }
//    );
    QString styleSheet = this->styleSheet();
    styleSheet += "QToolButton{border-style:flat}";
    styleSheet += "QToolButton:hover{border:2px solid grey;border-radius:5px}"
                  "QToolButton:checked{border:2px solid checked;border-radius:5px}";
    setStyleSheet(styleSheet);
}

PenState::PenState(const QColor& color, QWidget *parent) : IconButton(parent), penColor(color), penWidth(10) {

    QString styleSheet = this->styleSheet();
    styleSheet += "QToolButton{border-style:flat}";
    styleSheet += "QToolButton:hover{border:2px solid grey;border-radius:5px}"
                  "QToolButton:checked{border:2px solid checked;border-radius:5px}";
    setStyleSheet(styleSheet);

}

PenState::PenState(const int width, QWidget *parent) : IconButton(parent), penColor(Qt::black), penWidth(width) {
    QString styleSheet = this->styleSheet();
    styleSheet += "QToolButton{border-style:flat}";
    styleSheet += "QToolButton:hover{border:2px solid grey;border-radius:5px}"
                  "QToolButton:checked{border:2px solid checked;border-radius:5px}";
    setStyleSheet(styleSheet);
}

PenState::PenState(QWidget *parent) : IconButton(parent), penColor(Qt::black), penWidth(20) {
    QString styleSheet = this->styleSheet();
    styleSheet += "QToolButton{border-style:flat}";
    styleSheet += "QToolButton:hover{border:2px solid grey;border-radius:5px}"
                  "QToolButton:checked{border:2px solid checked;border-radius:5px}";
    setStyleSheet(styleSheet);
}


void PenState::paintEvent(QPaintEvent *event) {
    IconButton::paintEvent(event);

    QPainter painter(this);
    QPen pen;                                    //新建一个QPen对象
    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setColor(penColor);                        //设置画笔的颜色
    pen.setWidth(1);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);

    painter.setBrush(QBrush(penColor));
    painter.translate(width()/2, height()/2);
    painter.drawEllipse(QPoint(0, 0), penWidth, penWidth);
}
