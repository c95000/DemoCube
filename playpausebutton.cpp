#include "playpausebutton.h"
#include<iostream>
#include <QPainter>
#include <QPainter>
#include <QPaintEvent>

using namespace std;

PlayPauseButton::PlayPauseButton(QWidget *parent) : QPushButton(parent)
{
    QPixmap pixmap(":/images/res/images/media_control.png");
//    cout<<"save full screen failed"<<endl;

    for(int i = 0; i < 4; i++) {
        pixmapList.push_back(pixmap.copy(i * pixmap.width() / 4 + i, 0, pixmap.width()/4, pixmap.height()));
    }

    m_index=0;
    m_enter=false;

     setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}


void PlayPauseButton::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);
//     painter.drawPixmap(event->rect(), pixmapList[1]);
     painter.drawPixmap((width()-pixmapList.at(m_index).width())/2,
                        (height()-pixmapList.at(m_index).height())/2,
                        pixmapList.at(m_index).width(),
                        pixmapList.at(m_index).height(),
                        pixmapList.at(m_index));//画图画到中间
}

void PlayPauseButton::enterEvent(QEvent *event) {
    m_index=1;
        m_enter=true;
        update();
}

void PlayPauseButton::leaveEvent ( QEvent * event ) {
    m_index=0;
        m_enter=false;
        update();
}

void PlayPauseButton::mousePressEvent ( QMouseEvent * event ) {
    if(event->button()==Qt::LeftButton)//如果是左键按下
        {
            m_index=2;
            update();
            QPushButton::mousePressEvent(event);//返回到上级
        }

}

void PlayPauseButton::mouseReleaseEvent ( QMouseEvent * event ){
    if(event->button()==Qt::LeftButton)//如果是左键放下
        {
            m_index=1;
            update();
           QPushButton::mouseReleaseEvent(event);//返回到上级 引出按钮clicked信号
        }
}


QSize PlayPauseButton::sizeHint() const
{
    return QSize(pixmapList[0].width(), pixmapList[0].height());
}
