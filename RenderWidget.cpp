#include "RenderWidget.h"

#include <QPainter>
#include <QPaintEvent>
#include <QTime>

CRenderWidget::CRenderWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    _lpress = false;//初始鼠标左键未按下
         _drawType = 0;//初始为什么都不画
         _drag = 0;//默认非拖拽模式
         _begin = pos();//拖拽的参考坐标，方便计算位移
         _openflag = 0;//初始不打开图片
         _tEdit = new QTextEdit(this);//初始化文本输入框
         _tEdit->hide();//隐藏
         this->setGeometry(350,200,600,400);//设置窗体大小、位置
         setMouseTracking(true);//开启鼠标实时追踪，监听鼠标移动事件，默认只有按下时才监听
         //设置背景黑色
         //方法一
         QPalette palt(this->palette());
         palt.setColor(QPalette::Background, Qt::white);
         this->setAutoFillBackground(true);
         this->setPalette(palt);
         //方法二
         //this->setStyleSheet("background-color:yellow;");
}

void CRenderWidget::paintEvent(QPaintEvent *ev)
{
    if(0 == _drawType) {
        return;
    } else if(10 == _drawType) {
        QOpenGLWidget::paintEvent(ev);

        QPainter painter(this);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        QRect targetRect(0, 0, width(), height());

        QMutexLocker lock(&m_pixmapMutex);

        QRect srcRect(0, 0, m_currentFrame.width(), m_currentFrame.height());
        painter.drawImage(targetRect, m_currentFrame, srcRect);
        return;
    }
    if(_openflag == 0)//不是打开图片的，每一次新建一个空白的画布
    {
        _pixmap = QPixmap(size());//新建pixmap
        _pixmap.fill(Qt::white);//背景色填充为白色
    }
    QPixmap pix = _pixmap;//以_pixmap作为画布
    QPainter p(&pix);//将_pixmap作为画布
    p.setPen(Qt::red);
    unsigned int i1=0,i2=0,i3=0,i4=0,i5=0;//各种图形的索引

    for(int c = 0;c<_shape.size();++c)//控制用户当前所绘图形总数
    {
        if(_shape.at(c) == 1)//线条
        {
              const QVector<QPoint>& line = _lines.at(i1++);//取出一条线条
              for(int j=0; j<line.size()-1; ++j)//将线条的所有线段描绘出
              {
                  p.drawLine(line.at(j), line.at(j+1));
              }
        }
        else if(_shape.at(c) == 2)//矩形
        {
             p.drawRect(_rects.at(i2++));
        }
        else if(_shape.at(c) == 3)//椭圆
        {
            p.drawEllipse(_ellipse.at(i3++));
        }
        else if(_shape.at(c) == 4)//直线
        {
            p.drawLine(_line.at(i4).topLeft(),_line.at(i4).bottomRight());
            i4++;
        }
        else if(_shape.at(c) == 5)//文本
        {
            p.drawText(_tpoint.at(i5),_text.at(i5));
            i5++;
        }
    }
    p.end();
    p.begin(this);//将当前窗体作为画布
    p.drawPixmap(0,0, pix);//将pixmap画到窗体
}

void CRenderWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)//当鼠标左键按下
    {
        if(_drawType == 1)//线条(铅笔)
        {
            _lpress = true;//左键按下标志
            QVector<QPoint> line;//鼠标按下，新的线条开始
            _lines.append(line);//将新线条添加到线条集合
            QVector<QPoint>& lastLine = _lines.last();//拿到新线条
            lastLine.append(e->pos());//记录鼠标的坐标(新线条的开始坐标)
            _shape.append(1);
        }
        else if(_drawType == 2)//矩形
        {
            _lpress = true;//左键按下标志
            if(!_drag)//非拖拽模式
            {
                QRect rect;//鼠标按下，矩形开始
                _rects.append(rect);//将新矩形添加到矩形集合
                QRect& lastRect = _rects.last();//拿到新矩形
                lastRect.setTopLeft(e->pos());//记录鼠标的坐标(新矩形的左上角坐标)
                 _shape.append(2);
            }
            else if(_rects.last().contains(e->pos()))//拖拽模式、如果在矩形内按下
            {
                _begin = e->pos();//记录拖拽开始的坐标位置,方便计算位移

            }

        }
        else if(_drawType == 3)//椭圆
        {
            _lpress = true;//左键按下标志
            if(!_drag)//非拖拽模式
            {
                QRect rect;//鼠标按下，椭圆开始
                _ellipse.append(rect);//将新椭圆添加到椭圆集合
                QRect& lastEllipse = _ellipse.last();//拿到新椭圆
                lastEllipse.setTopLeft(e->pos());//记录鼠标的坐标(新椭圆的左上角坐标)
                 _shape.append(3);
            }
            else if(_ellipse.last().contains(e->pos()))//如果在椭圆内按下
            {
                _begin = e->pos();//记录拖拽开始的坐标位置

            }
        }
        else if(_drawType == 4)//直线
        {
            _lpress = true;//左键按下标志
            QRect rect;//鼠标按下，直线一端开始
            _line.append(rect);//将新直线添加到直线集合
            QRect& lastLine = _line.last();//拿到新直线
            lastLine.setTopLeft(e->pos());//记录鼠标的坐标(新直线开始一端坐标)
            _shape.append(4);
        }
        else if(_drawType == 5)//文字
        {
            update();//触发窗体重绘
            QPoint p;//鼠标按下，文字开始
            _tpoint.append(p);//将文字坐标添加到文字位置集合
            QPoint& lastp = _tpoint.last();//拿到新文字
            lastp = e->pos();//记录鼠标的坐标
            _tEdit->setGeometry(lastp.x()-6,lastp.y()-17,90,90);//设置文本框的位置、大小

            _tEdit->show();//显示文本输入框
            _text.append("");//添加文本到文本集合
            _tEdit->clear();//因为全局只有一个，所以使用之前要清空
            _shape.append(5);
        }

    }
}

void CRenderWidget::AddTexts()//当输入框文本改变时调用
{
    QString& last = _text.last();//拿到最后一个文本
    last = _tEdit->toPlainText();//将输入框文本作为文本
}

void CRenderWidget::renderShapes(QPainter& p) {
    p.setPen(Qt::red);
    unsigned int i1=0,i2=0,i3=0,i4=0,i5=0;//各种图形的索引

    for(int c = 0;c<_shape.size();++c)//控制用户当前所绘图形总数
    {
        if(_shape.at(c) == 1)//线条
        {
              const QVector<QPoint>& line = _lines.at(i1++);//取出一条线条
              for(int j=0; j<line.size()-1; ++j)//将线条的所有线段描绘出
              {
                  p.drawLine(line.at(j), line.at(j+1));
              }
        }
        else if(_shape.at(c) == 2)//矩形
        {
             p.drawRect(_rects.at(i2++));
        }
        else if(_shape.at(c) == 3)//椭圆
        {
            p.drawEllipse(_ellipse.at(i3++));
        }
        else if(_shape.at(c) == 4)//直线
        {
            p.drawLine(_line.at(i4).topLeft(),_line.at(i4).bottomRight());
            i4++;
        }
        else if(_shape.at(c) == 5)//文本
        {
            p.drawText(_tpoint.at(i5),_text.at(i5));
            i5++;
        }
    }
    p.end();
}

void CRenderWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(_drag && ((_drawType == 2 && _rects.last().contains(e->pos()))
            || (_drawType == 3 && _ellipse.last().contains(e->pos()) )))
    {
        setCursor(Qt::SizeAllCursor);//拖拽模式下，并且在拖拽图形中，将光标形状改为十字
    }
    else
    {
        setCursor(Qt::ArrowCursor);//恢复原始光标形状
        _drag = 0;
    }

    if(_lpress)
    {
        if(_drawType == 1)//铅笔画线
        {
            if(_lines.size()<=0) return;//线条集合为空，不画线
            QVector<QPoint>& lastLine = _lines.last();//最后添加的线条，就是最新画的
            lastLine.append(e->pos());//记录鼠标的坐标(线条的轨迹)
            update();//触发窗体重绘
        }
        else if(_drawType == 2)
        {
            if(_drag == 0)//非拖拽
            {
                QRect& lastRect = _rects.last();//拿到新矩形
                lastRect.setBottomRight(e->pos());//更新矩形的右下角坐标
            }
            else//拖拽模式
            {
                QRect& lastRect = _rects.last();//拿到最后添加的矩形
                if(lastRect.contains(e->pos()))//在矩形的内部
                {
                    int dx = e->pos().x()-_begin.x();//横向移动x
                    int dy = e->pos().y()-_begin.y();//纵向移动y
                    lastRect = lastRect.adjusted(dx,dy,dx,dy);//更新矩形的位置
                    _begin = e->pos();//刷新拖拽点起始坐标
                }

            }
            update();//触发窗体重绘

        }
        else if(_drawType == 3)
        {
            if(_drag == 0)//非拖拽
            {
                QRect& lastEllipse = _ellipse.last();//拿到新椭圆
                lastEllipse.setBottomRight(e->pos());//更新椭圆的右下角坐标)

            }
            else//拖拽
            {
                QRect& lastEllipse = _ellipse.last();//拿到最后添加的矩形
                if(lastEllipse.contains(e->pos()))//在椭圆内部
                {
                    int dx = e->pos().x()-_begin.x();//横向移动x
                    int dy = e->pos().y()-_begin.y();//纵向移动y
                    lastEllipse = lastEllipse.adjusted(dx,dy,dx,dy);
                    _begin = e->pos();//刷新拖拽点起始坐标
                }

            }
            update();//触发窗体重绘
        }
        else if(_drawType == 4)
        {
            QRect& lastLine = _line.last();//拿到新直线
            lastLine.setBottomRight(e->pos());//更新直线另一端)
            update();//触发窗体重绘
        }
    }


}

void CRenderWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(_lpress)
    {
        if(_drawType == 1)
        {
            QVector<QPoint>& lastLine = _lines.last();//最后添加的线条，就是最新画的
            lastLine.append(e->pos());//记录线条的结束坐标
            _lpress = false;//标志左键释放
        }
        else if(_drawType == 2)
        {
            QRect& lastRect = _rects.last();//拿到新矩形
            if(!_drag)
            {
                lastRect.setBottomRight(e->pos());//不是拖拽时，更新矩形的右下角坐标)
                //刚画完矩形，将光标设置到新矩形的中心位置，并进入拖拽模式
                this->cursor().setPos(this->cursor().pos().x()-lastRect.width()/2,this->cursor().pos().y()-lastRect.height()/2);
                _drag = 1;

            }
            _lpress = false;

        }
        else if(_drawType == 3)
        {
            QRect& lastEllipse = _ellipse.last();//拿到新椭圆
            if(!_drag)
            {
                lastEllipse.setBottomRight(e->pos());//不是拖拽时，更新椭圆的右下角坐标)
                //刚画完椭圆，将光标设置到新椭圆的中心位置，并进入拖拽模式
                this->cursor().setPos(this->cursor().pos().x()-lastEllipse.width()/2,this->cursor().pos().y()-lastEllipse.height()/2);
                _drag = 1;

            }
            _lpress = false;
        }
        else if(_drawType == 4)
        {
            QRect& lastLine = _line.last();//拿到新矩形
            lastLine.setBottomRight(e->pos());//更新矩形的右下角坐标)
            _lpress = false;

        }
    }
}

void CRenderWidget::Lines()
{
    _drawType = 1;//铅笔
    _tEdit->hide();//文本框隐藏
}

void CRenderWidget::Line()
{
    _drawType = 4;//直线
    _tEdit->hide();
}

void CRenderWidget::Rects()
{
    _drawType = 2;//矩形
    _tEdit->hide();

}

void CRenderWidget::Ellipses()
{
    _drawType = 3;//椭圆
    _tEdit->hide();
}

void CRenderWidget::Texts()
{
    _drawType = 5;//文字
}

void CRenderWidget::SavePic()
{
    //弹出文件保存对话框
    //QString fileName = QFileDialog::getSaveFileName(this, tr("保存"), "new.jpg", "Image (*.jpg *.png *.bmp)");
    QString fileName = "full-";
    fileName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".jpg";
    if (fileName.length() > 0)
    {
#if 0
        QRect rect = this->geometry();
        QPixmap p = this->grab(rect);
        p.save(fileName, "jpg");
#endif



        if(10 == _drawType) {
            QPixmap pixmap = QPixmap::fromImage(m_currentFrame);
            pixmap.save(fileName);
        } else if(1 == _drawType) {
            QPixmap pixmap(size());//新建窗体大小的pixmap
            QPainter painter(&_pixmap);//将pixmap作为画布
            //painter.fillRect(QRect(0, 0, size().width(), size().height()), Qt::white);//设置绘画区域、画布颜色
            //this->render(&painter);//将窗体渲染到painter，再由painter画到画布
            renderShapes(painter);
            //painter.begin(this);//将当前窗体作为画布
            //painter.drawPixmap(0,0, pixmap);//将pixmap画到窗体
            _pixmap.save(fileName);
        }
        #if 0
        _tEdit->hide();//防止文本输入框显示时，将文本框保存到图片
        QPixmap pixmap(size());//新建窗体大小的pixmap
        QPainter painter(&pixmap);//将pixmap作为画布
        painter.fillRect(QRect(0, 0, size().width(), size().height()), Qt::white);//设置绘画区域、画布颜色
        //this->render(&painter);//将窗体渲染到painter，再由painter画到画布
        pixmap.copy(QRect(0,0,size().width(),size().height())).save(fileName);//不包含工具栏
#endif
    }
}

void CRenderWidget::OpenPic()
{
    //弹出文件打开对话框
    QString picPath = QFileDialog::getOpenFileName(this,tr("打开"),"","Image Files(*.jpg *.png)");
    if(!picPath.isEmpty())//用户选择了文件
    {
        QPixmap pix;
        pix.load(picPath);//加载图片
        QPainter p(&_pixmap);
        p.drawPixmap(0,30,pix);//添加工具栏的空间
        _openflag = 1;//设置文件打开标志
        update();//触发窗体重绘，将图片画到窗体
    }
}

void CRenderWidget::contextMenuEvent(QContextMenuEvent *)  //右键菜单事件
{
    _Rmenu->exec(cursor().pos());//在光标位置弹出菜单
}

void CRenderWidget::keyPressEvent(QKeyEvent *e) //按键事件
{
     //Ctrl+Z撤销
     if (e->key() == Qt::Key_Z && e->modifiers() == Qt::ControlModifier)
     {
         if(_shape.size()>0)
         {
             switch(_shape.last())
             {
                 case 1: _lines.pop_back();
                         break;
                 case 2: _rects.pop_back();
                         break;
                 case 3: _ellipse.pop_back();
                         break;
                 case 4: _line.pop_back();
                         break;
             }
             _shape.pop_back();
             _drag = 0;//设置为非拖拽模式
             update();
         }
     }
     else if (e->key() == Qt::Key_S && e->modifiers() == Qt::ControlModifier)//保存
     {
        SavePic();//Ctrl+S保存
     }
}

void CRenderWidget::clear() //按键事件
{
    _lines.clear();
    _shape.clear();
    update();
}

void CRenderWidget::whiteBoard() //按键事件
{
    _drawType = 1;
    _pixmap = QPixmap(size());//新建pixmap
    _pixmap.fill(Qt::white);//背景色填充为白色
    update();
}

void CRenderWidget::playVideo() //按键事件
{
    _drawType = 10;
    update();
}


void CRenderWidget::loadPixmap() //按键事件
{
    QPixmap pixmap = QPixmap::fromImage(m_currentFrame);

    int with = this->width();
    int height = this->height();
    //QPixmap fitpixmap = p.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    //this->setPixmap(fitpixmap);
    _pixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    _openflag = 1;//设置文件打开标志
    _drawType = 1;
    update();
}

void CRenderWidget::setPixmap(const QImage &p)
{
    QMutexLocker lock(&m_pixmapMutex);
    // [TODO] - prevent memory copy
    m_currentFrame = p;
    update();
}

void CRenderWidget::getCurrentPixmap(QImage &p)
{
    QMutexLocker lock(&m_pixmapMutex);
    // [TODO] - prevent memory copy
    p = m_currentFrame;
}

void CRenderWidget::onRender(const QImage &pixmap) {
    QMutexLocker lock(&m_pixmapMutex);
    // [TODO] - prevent memory copy
    m_currentFrame = pixmap;
    update();
}

//void CRenderWidget::paintEvent(QPaintEvent *ev)
//{
//    QOpenGLWidget::paintEvent(ev);

//    QPainter painter(this);
//    painter.setRenderHint(QPainter::SmoothPixmapTransform);
//    QRect targetRect(0, 0, width(), height());

//    QMutexLocker lock(&m_pixmapMutex);

//    QRect srcRect(0, 0, m_currentFrame.width(), m_currentFrame.height());
//    painter.drawImage(targetRect, m_currentFrame, srcRect);

//    //QPixmap _pixmap = QPixmap(size());//新建pixmap
//    //_pixmap.fill(Qt::white);//背景色填充为白色
//    //painter.drawPixmap(0,0, _pixmap);//将pixmap画到窗体
//}
