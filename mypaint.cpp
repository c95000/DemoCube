#include "mypaint.h"
#include "CommentToolBar.h"
#include "common.h"
#include "QBoxLayout"
#include <QDateTime>

MyPaint::MyPaint(QWidget *parent) :
    QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _lpress = false;//初始鼠标左键未按下
         _drawType = 1;//初始为什么都不画
         _drag = 0;//默认非拖拽模式
         _begin = pos();//拖拽的参考坐标，方便计算位移
         _openflag = 0;//初始不打开图片

         penColor = Qt::red;
         penSize = 1;

         printf("[%p]_openflag:%d", this,  _openflag);
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

        commonToolBar = new CommentToolBar(this);

        QVBoxLayout* layout = new QVBoxLayout();
//        layout->addWidget(commonToolBar, 1, Qt::AlignBottom);
        layout->addWidget(commonToolBar);
        setLayout(layout);

        connect(commonToolBar->closeButton(), SIGNAL(clicked()), this, SLOT(close()));
        connect(commonToolBar->rubberButton(), SIGNAL(clicked()), this, SLOT(rubber()));
        connect(commonToolBar->whiteboardButton(), SIGNAL(clicked()), this, SLOT(whiteboard()));

        connect(commonToolBar->redPenButton(), SIGNAL(clicked()), this, SLOT(redPen()));
        connect(commonToolBar->blackPenButton(), SIGNAL(clicked()), this, SLOT(blackPen()));
        connect(commonToolBar->whitePenButton(), SIGNAL(clicked()), this, SLOT(whitePen()));

        connect(commonToolBar->penSize1Button(), SIGNAL(clicked()), this, SLOT(penSize1()));
        connect(commonToolBar->penSize2Button(), SIGNAL(clicked()), this, SLOT(penSize2()));
        connect(commonToolBar->penSize3Button(), SIGNAL(clicked()), this, SLOT(penSize3()));


#if 0
        //创建工具栏
        QToolBar *tbar = addToolBar(tr("工具栏"));   
        tbar->setMovable(false);//工具栏不可移动
        tbar->setIconSize(QSize(16, 16));//设置动作图标的尺寸
        tbar->setStyleSheet("background-color:rgb(199,237,204)");//背景色

        _Rmenu = new QMenu(this);//创建右键菜单
        _Rmenu->addAction(tr("保存  \tCtrl+S"), this, SLOT(SavePic()));//添加菜单动作
        _Rmenu->addAction(tr("退出  \tALT+F4"), this, SLOT(close()));//添加菜单动作
        _Rmenu->setStyleSheet("background-color:rgb(199,237,204)");//设置背景色

        QAction *openAction = new QAction(tr("&打开"), this);//打开动作
        openAction->setIcon(QIcon(":/png/images/open.png"));//图标
        openAction->setShortcut(QKeySequence(tr("Ctrl+O")));//热键
        tbar->addAction(openAction);//添加到工具栏

        QAction *saveAction = new QAction(tr("&保存"), this);//保存动作
        saveAction->setIcon(QIcon(":/png/images/save.png"));//图标
        saveAction->setShortcut(QKeySequence(tr("Ctrl+S")));//热键
        tbar->addAction(saveAction);//添加到工具栏

        QAction *saveasAction = new QAction(tr("&另存为"), this);//保存动作
        saveasAction->setIcon(QIcon(":/png/images/saveas.png"));//图标
        saveasAction->setShortcut(QKeySequence(tr("Ctrl+ALT+S")));//热键
        tbar->addAction(saveasAction);//添加到工具栏

        QAction *lineAction = new QAction(tr("&直线"), this);//直线动作
        lineAction->setIcon(QIcon(":/png/images/line.png"));//图标
        lineAction->setShortcut(QKeySequence(tr("Ctrl+L")));//热键
        tbar->addAction(lineAction);//添加到工具栏

        QAction *linesAction = new QAction(tr("&铅笔"), this);//铅笔动作
        linesAction->setIcon(QIcon(":/png/images/lines.png"));//图标
        linesAction->setShortcut(QKeySequence(tr("Ctrl+P")));//热键
        tbar->addAction(linesAction);//添加到工具栏

        QAction *rectAction = new QAction(tr("&矩形"), this);//矩形动作
        rectAction->setIcon(QIcon(":/png/images/rect.png"));//图标
        rectAction->setShortcut(QKeySequence(tr("Ctrl+R")));//热键
        tbar->addAction(rectAction);

        QAction *ellipseAction = new QAction(tr("&椭圆"), this);//椭圆动作
        ellipseAction->setIcon(QIcon(":/png/images/ellipse.png"));//图标
        ellipseAction->setShortcut(QKeySequence(tr("Ctrl+E")));//热键
        tbar->addAction(ellipseAction);

        QAction *textAction = new QAction(tr("&文字"), this);//文字动作
        textAction->setIcon(QIcon(":/png/images/texts.png"));//图标
        textAction->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
        tbar->addAction(textAction);

        //连接信号与槽函数
        connect(linesAction, SIGNAL(triggered()), this, SLOT(Lines()));
        connect(rectAction, SIGNAL(triggered()), this, SLOT(Rects()));
        connect(ellipseAction, SIGNAL(triggered()), this, SLOT(Ellipses()));
        connect(lineAction, SIGNAL(triggered()), this, SLOT(Line()));
        connect(saveAction, SIGNAL(triggered()), this, SLOT(SavePic()));
        connect(openAction, SIGNAL(triggered()), this, SLOT(OpenPic()));
        connect(textAction, SIGNAL(triggered()), this, SLOT(Texts()));
        connect(_tEdit, SIGNAL(textChanged()), this, SLOT(AddTexts()));
#endif
}

MyPaint::~MyPaint()
{
    delete commonToolBar;
}


void MyPaint::paintEvent(QPaintEvent *)
{
    if(_openflag == 0)//不是打开图片的，每一次新建一个空白的画布
    {
        _pixmap = QPixmap(size());//新建pixmap
        _pixmap.fill(Qt::white);//背景色填充为白色
    }
    QPixmap pix = _pixmap;//以_pixmap作为画布
    QPainter p(&pix);//将_pixmap作为画布
    unsigned int i1=0,i2=0,i3=0,i4=0,i5=0;//各种图形的索引

    for(int c = 0;c<_shape.size();++c)//控制用户当前所绘图形总数
    {
//        p.setPen(_penColor.at(c));
        p.setPen(QPen(_penColor.at(c), _penSize.at(c)));
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

void MyPaint::mousePressEvent(QMouseEvent *e)
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

        QColor currentColor = penColor;
        _penColor.append(currentColor);
        _penSize.append(penSize);
    }
}

void MyPaint::AddTexts()//当输入框文本改变时调用
{
    QString& last = _text.last();//拿到最后一个文本
    last = _tEdit->toPlainText();//将输入框文本作为文本
}

void MyPaint::redPen() {
    penColor = Qt::red;
}
void MyPaint::whitePen() {
    penColor = Qt::green;
}
void MyPaint::blackPen(){
    penColor = Qt::black;
}
void MyPaint::rubber(){
    revoke();
}

void MyPaint::close() {
    SavePic();
}

void MyPaint::whiteboard() {
    clear();
    update();
}

void MyPaint::penSize1() {
    penSize = 1;
}
void MyPaint::penSize2() {
    penSize = 3;
}
void MyPaint::penSize3() {
    penSize = 5;
}

void MyPaint::mouseMoveEvent(QMouseEvent *e)
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

void MyPaint::mouseReleaseEvent(QMouseEvent *e)
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

void MyPaint::Lines()
{
    _drawType = 1;//铅笔
    _tEdit->hide();//文本框隐藏
}

void MyPaint::Line()
{
    _drawType = 4;//直线
    _tEdit->hide();
}

void MyPaint::Rects()
{
    _drawType = 2;//矩形
    _tEdit->hide();

}

void MyPaint::Ellipses()
{
    _drawType = 3;//椭圆
    _tEdit->hide();
}

void MyPaint::Texts()
{
    _drawType = 5;//文字
}

void MyPaint::SavePic()
{
    //弹出文件保存对话框
//    QString fileName = QFileDialog::getSaveFileName(this, tr("保存"), "new.jpg", "Image (*.jpg *.png *.bmp)");

    QString fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
    fileName += ".png";

    if (fileName.length() > 0)
    {
        QByteArray qb;
        printf("fileName:%s ", qb.append(fileName).data());
        printf("%d x %d", size().width(), size().height());
        commonToolBar->hide();
        _tEdit->hide();//防止文本输入框显示时，将文本框保存到图片
        QPixmap pixmap(size());//新建窗体大小的pixmap
        QPainter painter(&pixmap);//将pixmap作为画布
        painter.fillRect(QRect(0, 0, size().width(), size().height()), Qt::white);//设置绘画区域、画布颜色
        this->render(&painter);//将窗体渲染到painter，再由painter画到画布
        commonToolBar->show();
        pixmap.copy().save(fileName);//不包含工具栏

//        QRect rect = geometry();
//        printf("x:%d y:%d  %d x %d", rect.x(), rect.y(), rect.width(), rect.height());
//        QPixmap pixmap = this->grab(QRect(0, 0, width(), height()));
//        pixmap.save(fileName);
    }

//    QRect rect = geometry();
//    QPixmap p = this->grab(rect);

//    QString filePathName = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
//    filePathName += ".png";
//    if(!p.save(filePathName,"png"))
//    {
//        printf("save widget screen failed");
//    }

}

void MyPaint::OpenPic()
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

void MyPaint::contextMenuEvent(QContextMenuEvent *)  //右键菜单事件
{
    _Rmenu->exec(cursor().pos());//在光标位置弹出菜单
}

void MyPaint::keyPressEvent(QKeyEvent *e) //按键事件
{
     //Ctrl+Z撤销
     if (e->key() == Qt::Key_Z && e->modifiers() == Qt::ControlModifier)
     {
        revoke();
     }
     else if (e->key() == Qt::Key_S && e->modifiers() == Qt::ControlModifier)//保存
     {
        SavePic();//Ctrl+S保存
     }
}

void MyPaint::revoke() {
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
        _penSize.pop_back();
        _penColor.pop_back();
        _drag = 0;//设置为非拖拽模式
        update();
    }
}

void MyPaint::clear() //按键事件
{
     _openflag = 0;
    _lines.clear();
    _shape.clear();
    _penColor.clear();
    _penSize.clear();
    update();
}

void MyPaint::loadPixmap(QPixmap& p) //按键事件
{
    int with = this->width();
    int height = this->height();
    //QPixmap fitpixmap = p.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    //this->setPixmap(fitpixmap);
    _pixmap = p.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    _openflag = 1;//设置文件打开标志
    printf("[%p] loadPixmap _openflag:%d", this, _openflag);
    update();
}
