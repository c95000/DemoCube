#include "ImageButton.h"

#include<iostream>
#include <QPainter>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>
#include <QPaintEvent>
#include <QBitmap>

#include <QDebug>
#define printf qDebug

using namespace std;

ImageButton::ImageButton(QWidget *parent) : QPushButton(parent)
{
    QPixmap pixmap(":/images/res/images/media_control.png");

    for(int i = 0; i < 4; i++) {
        pixmapList.push_back(pixmap.copy(i * pixmap.width() / 4 + i, 0, pixmap.width()/4, pixmap.height()));
    }

    m_index=0;
    m_enter=false;

//   setStyleSheet ("background-color: rgb(255, 0, 255);");
   setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
   setFixedSize(pixmapList[0].width(), pixmapList[0].height());
   //setMask(QBitmap(pixmapList[0].mask()));
}


void ImageButton::paintEvent(QPaintEvent *event)
{
//    QPushButton::paintEvent(event);
     QPainter painter(this);
     painter.setBrush(QBrush(Qt::red, Qt::CrossPattern));
//     painter.drawRect(0,0, width(), height());
//     painter.drawPixmap(event->rect(), pixmapList[1]);
     painter.drawPixmap((width()-pixmapList.at(m_index).width())/2,
                        (height()-pixmapList.at(m_index).height())/2,
                        pixmapList.at(m_index).width(),
                        pixmapList.at(m_index).height(),
                        pixmapList.at(m_index));//画图画到中间

//     painter.background();
//     QPixmap pixmap = QPixmap(size());
//     pixmap.fill(Qt::green);
//     painter.drawPixmap(0, 0, pixmap);
}

void ImageButton::enterEvent(QEvent *event) {
    m_index=1;
        m_enter=true;
        update();
}

void ImageButton::leaveEvent ( QEvent * event ) {
    m_index=0;
        m_enter=false;
        update();
}

void ImageButton::mousePressEvent ( QMouseEvent * event ) {
    if(event->button()==Qt::LeftButton)//如果是左键按下
        {
            m_index=2;
            update();
            QPushButton::mousePressEvent(event);//返回到上级
        }

}

void ImageButton::mouseReleaseEvent ( QMouseEvent * event ){
    if(event->button()==Qt::LeftButton)//如果是左键放下
        {
            m_index=1;
            update();
           QPushButton::mouseReleaseEvent(event);//返回到上级 引出按钮clicked信号
        }
}

//QSize ImageButton::sizeHint() const
//{
//    return QSize(pixmapList[0].width(), pixmapList[0].height());
//}

//void ImageButton::resizeEvent(QResizeEvent *event) {

//    printf("x:%d y:%d l:%d t:%d r:%d b:%d w:%d h:%d", this->geometry().x(), this->geometry().y(),
//           this->geometry().left(), this->geometry().top(), this->geometry().right(), this->geometry().bottom(),
//           this->geometry().width(), this->geometry().height());

////    this->setGeometry(0, 0, 20, 20);

////    QWidget* parent = this->parentWidget();
////    int cx = 0;
////    int cy = 0;
////    if(NULL != parent) {
////        cx = (parent->width() - width())/2;
////        cy = (parent->height() - height())/2;
////        printf("&p(%d x %d) me(%d x %d)", parent->width(), parent->height(), width(), height());
////    }
////    move(20, 20);
//   //printf("resizeEvent p(%d x %d) me(%d x %d)", this->parentWidget()->width(), this->parentWidget()->height(), event->size().width(), event->size().height());
//}
