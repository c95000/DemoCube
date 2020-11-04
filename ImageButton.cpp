#include "ImageButton.h"

#include <iostream>
#include <QPainter>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>
#include <QPaintEvent>
#include <QBitmap>

#include "common.h"

using namespace std;

ImageButton::ImageButton(QWidget *parent) : QPushButton(parent)
{
    QPixmap pixmap(":/images/res/images/default.png");
    pixmap = pixmap.scaled(QSize(60, 60), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    for(int i = 0; i < 4; i++) {
//        pixmapList.push_back(pixmap.copy(i * pixmap.width() / 4 + i, 0, pixmap.width()/4, pixmap.height()));
        pixmapList.push_back(pixmap.copy());
    }

    m_index=0;
    m_enter=false;

//   setStyleSheet ("background-color: rgb(255, 0, 255);");
   setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
   setFixedSize(pixmapList[0].width(), pixmapList[0].height());
   //setMask(QBitmap(pixmapList[0].mask()));

//   connect(this, SIGNAL(clicked()), this, SLOT(mouseClicked()));
}


void ImageButton::paintEvent(QPaintEvent *event)
{
//    QPushButton::paintEvent(event);
     QPainter painter(this);
     painter.setBrush(QBrush(Qt::red, Qt::CrossPattern));
//     painter.drawRect(0,0, width(), height());
//     painter.drawPixmap(event->rect(), pixmapList[1]);
     if(m_index == 1) {
         painter.drawPixmap((width()-pixmapList.at(m_index).width())/2,
                            (height()-pixmapList.at(m_index).height())/2,
                            pixmapList.at(m_index).width(),
                            pixmapList.at(m_index).height(),
                            pixmapList.at(m_index));//画图画到中间
     } else {
         painter.drawPixmap((width()-pixmapList.at(m_index).width())/2 + 2,
                            (height()-pixmapList.at(m_index).height())/2 + 2,
                            pixmapList.at(m_index).width(),
                            pixmapList.at(m_index).height(),
                            pixmapList.at(m_index));//画图画到中间
    }


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

void ImageButton::setFixedSize(int w, int h) {
    QPushButton::setFixedSize(w + 3, h + 3);
}

void ImageButton::setImages(const QPixmap &pixmaps) {
//    setImages(pixmaps, pixmaps.width(), pixmaps.height());
    setImages(pixmaps, pixmapList[0].width(), pixmapList[0].width());
}

void ImageButton::setImages(const QPixmap &pixmaps, int width, int height) {
    QPixmap pixmap = pixmaps;
    if(pixmap.width() != width || pixmap.height() != height) {
        pixmap = pixmaps.scaled(QSize(width, height), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    pixmapList.clear();
    for(int i = 0; i < 4; i++) {
        pixmapList.push_back(pixmap.copy());
    }
    setFixedSize(width, height);
    update();
}

void ImageButton::setImages(const QString imgsrc)
{
    QPixmap pixmap(imgsrc);
    setImages(pixmap, pixmap.width(), pixmap.height());
}

void ImageButton::setImages(const QString imgsrc, int width, int height) {
    QPixmap pixmap(imgsrc);
    setImages(pixmap, width, height);
}
