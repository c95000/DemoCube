#include "linestate.h"
#include "ui_linestate.h"
#include <QPen>
#include <QPainter>
#include <QResizeEvent>
#include "common.h"
#include "qpainterpath.h"

LineState::LineState(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineState),
    lineColor(Qt::black),
    lineWidth(5)
{
    ui->setupUi(this);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(228,228,228)); //设置背景黑色
    setAutoFillBackground(true);
    setPalette(pal);
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

    painter.setPen(QColor(160, 160, 160));
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
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);

    int x = 8;
    int y = (size().height()) / 2;
//    painter.drawLine(x, y, size().width() - x, y);

// 曲线上的点
    static QList<QPointF> points = QList<QPointF>() << QPointF(8, 0) << QPointF(width()/2-5, -3)
                                                    << QPointF(width()/2+5, 3) << QPointF(width()-8, 0);
    QPainterPath path(points[0]);
    for (int i = 0; i < points.size() - 1; ++i) {
        // 控制点的 x 坐标为 sp 与 ep 的 x 坐标和的一半
        // 第一个控制点 c1 的 y 坐标为起始点 sp 的 y 坐标
        // 第二个控制点 c2 的 y 坐标为结束点 ep 的 y 坐标
        QPointF sp = points[i];
        QPointF ep = points[i+1];
        QPointF c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
        QPointF c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
        //        QPointF c2 = QPointF(ep.x(), (sp.y() + ep.y()) / 2);
        path.cubicTo(c1, c2, ep);
    }

    painter.setRenderHint(QPainter::Antialiasing, true);
    // 绘制 path
    //移动默认(0,0)到(40,130)
    painter.translate(0, height()/2);
    painter.drawPath(path);

    // 绘制曲线上的点
    //        painter.setBrush(Qt::gray);
    //        for (int i = 0; i < points.size(); ++i) {
    //            painter.drawEllipse(points[i], 4, 4);
    //        }
}
