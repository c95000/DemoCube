#include "penstyle.h"
#include "pensettingdialog.h"
#include "qpainterpath.h"


PenStyle::PenStyle(QWidget *parent) : IconButton(parent)
  ,lineColor(Qt::black)
  ,lineWidth(5)
{
//    connect(this, &QPushButton::pressed, [=](){
//        printf("pressed");
////        this->setIcon(icon2);
//    }
//    );
//    connect(this, &QPushButton::released, [=](){
//        printf("released");
////        this->setIcon(icon1);
//    }
//    );

    connect(this, &QPushButton::clicked, [=](){
        printf("clicked");
//        PenSettingDialog *dlg=new PenSettingDialog(this);
        PenSettingDialog *dlg=new PenSettingDialog(lineColor, lineWidth, this);

        int ret = dlg->exec();
        if(ret==QDialog::Accepted) {
            printf("!ret:%d", ret);
            lineColor = dlg->getColor();
            lineWidth = dlg->getWidth();
            update();
        } else {
            printf("ret:%d", ret);
        }
        delete dlg;
        }
    );
}

PenStyle::PenStyle(const QColor& color, const int width, QWidget *parent) : IconButton(tr(":/res/icons/pen_style.svg"), tr(":/res/icons/pen_style.svg"), parent)
  ,lineColor(color)
  ,lineWidth(width) {
    connect(this, &QPushButton::clicked, [=](){
        printf("clicked");
//        PenSettingDialog *dlg=new PenSettingDialog(this);
        PenSettingDialog *dlg=new PenSettingDialog(lineColor, lineWidth, this);

        int ret = dlg->exec();
        if(ret==QDialog::Accepted) {
            printf("!ret:%d", ret);
            lineColor = dlg->getColor();
            lineWidth = dlg->getWidth();
            update();
            emit onPenChanged(lineColor.rgb(), lineWidth);
        } else {
            printf("ret:%d", ret);
        }
        delete dlg;
        }
    );
}

QColor PenStyle::getColor() const {
    return lineColor;
}

int PenStyle::getWidth() const {
    return lineWidth;
}

void PenStyle::paintEvent(QPaintEvent *event) {
    IconButton::paintEvent(event);

    QPainter painter(this);
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
    static QList<QPointF> points = QList<QPointF>() << QPointF(8, 0) << QPointF(width()/2-5, -5)
                                                    << QPointF(width()/2+5, 5) << QPointF(width()-8, 0);
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


