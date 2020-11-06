#include "freedrawing.h"
#include "ui_freedrawing.h"
#include <QPainter>
#include "common.h"
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>

FreeDrawing::FreeDrawing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FreeDrawing)
{
    ui->setupUi(this);
    printf("size: %d x %d", size().width(), size().height());

    freeDrawingMenu = new FreeDrawingMenu();
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(freeDrawingMenu, 0, Qt::AlignBottom);
    setLayout(hLayout);

    connect(freeDrawingMenu, &FreeDrawingMenu::penChanged, this, &FreeDrawing::on_penChanged);
    connect(freeDrawingMenu, &FreeDrawingMenu::signalUndo, this, &FreeDrawing::on_undo);
    connect(freeDrawingMenu, &FreeDrawingMenu::signalClose, this, &FreeDrawing::on_close);
}

FreeDrawing::FreeDrawing(const QString& imageSource, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FreeDrawing)
{
    _originPixmap.load(imageSource);
    ui->setupUi(this);
}

FreeDrawing::FreeDrawing(const QPixmap& pixmapSource, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FreeDrawing)
{
    _originPixmap = pixmapSource.copy();
    ui->setupUi(this);
}

FreeDrawing::~FreeDrawing()
{
    printf("FreeDrawing is deleted.");
    for(int i = 0; i < _lines.size(); i++) {
        _lines[i].clear();
    }
    _lines.clear();
    delete ui;
}

void FreeDrawing::on_penChanged() {
    printf("colorIndex: width:%d", freeDrawingMenu->getPenWidth());
//    m_pen->setColor(freeDrawingMenu->penColor());
//    m_pen->setWidth(freeDrawingMenu->penWidth());
    penColor = freeDrawingMenu->getPenColor();
    penWidth = freeDrawingMenu->getPenWidth();
}

void FreeDrawing::on_undo() {
    if(_lines.size() > 0) {
        _lines.takeLast().clear();
        _lineWidth.removeLast();
        _lineColors.removeLast();
        update();
    }
}
void FreeDrawing::on_close() {
    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".png";
    printf("filename: %s", fileName.toStdString().c_str());
    if (fileName.length() > 0)
    {
        freeDrawingMenu->hide();//不包含工具栏
        QPixmap pixmap = grab();
        freeDrawingMenu->show();
        pixmap.save(fileName);
    }
    emit signalClose();
}

void FreeDrawing::paintEvent(QPaintEvent *) {
    QPixmap pixmap(size());
    pixmap.fill(Qt::white);

//    printf("xxx size: %d x %d", size().width(), size().height());

//    QPainter painter;//将_pixmap作为画布
//    painter.begin(&_pixmap);

////    painter.end();
////    painter.drawPixmap(0, 0, width(), height(), pixmap);//将pixmap画到窗体

//    QPen pen;                                    //新建一个QPen对象
////    pen.setStyle (Qt::PenStyle::SolidLine);
//    pen.setColor(freeDrawingMenu->penColor());                        //设置画笔的颜色
//    pen.setWidth(freeDrawingMenu->penWidth());

////    printf("lines: %d", _lines.size());
//    for(int i = 0; i < _lines.size(); i++) {
//        const QVector<QPoint>& line = _lines.at(i);
//        printf("line points: %d", line.size());
//        for(int j = 0; j < line.size() - 1; j++) {
//            painter.drawLine(line.at(j), line.at(j+1));
//        }
//    }
//    painter.end();

//    painter.begin(this);
//    painter.drawPixmap(0, 0, width(), height(), _pixmap);//将pixmap画到窗体

    QPainter painter;//将_pixmap作为画布
    painter.begin(this);
//    painter.setPen(penColor);
//    painter.setPen(penWidth);
//    painter.setPen(QPen(penColor, penWidth));
    painter.drawPixmap(0, 0, pixmap);//将pixmap画到窗体
    if(_originPixmap.width() > 0 && _originPixmap.height() > 0) {
        double ratio = 1.0 * _originPixmap.width() / _originPixmap.height();
        double viewRatio = 1.0 * width()/height();

        QRect rect;

        if(ratio > viewRatio) {
            int w = width();
            int h = width() / ratio;
            int offsetX = 0;
            int offsetY = (height() - h) / 2;
            rect.setWidth(w);
            rect.setHeight(h);
            rect.moveTo(offsetX, offsetY);
//            painter.drawPixmap(0, 0, width(), width() / ratio , _originPixmap);//将pixmap画到窗体
        } else {
            int w = height() * ratio;
            int h = height();
            int offsetX = (width() - w) / 2;
            int offsetY = 0;
            rect.setWidth(w);
            rect.setHeight(h);
            rect.moveTo(offsetX, offsetY);
//            painter.drawPixmap(0, 0, height() * ratio, height() , _originPixmap);//将pixmap画到窗体
        }

        painter.drawPixmap(rect , _originPixmap);//将pixmap画到窗体
    }

//    printf("_lines:%d", _lines.size());
//    printf("_lineColors:%d", _lineColors.size());
//    printf("_lineWidth:%d", _lineWidth.size());

    for(int i = 0; i < _lines.size(); i++) {
        const QVector<QPoint>& line = _lines.at(i);
//        printf("line[%d]:%d", i, line.size());
        QPen pen(_lineColors.at(i), _lineWidth.at(i));
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen);
        for(int j = 0; j < line.size() - 1; j++) {
            painter.drawLine(line.at(j), line.at(j+1));
        }
    }

    painter.end();
}

void FreeDrawing::mousePressEvent(QMouseEvent *e) {
//    printf("mousePressEvent e->pos(%d, %d) \n", e->pos().rx(), e->pos().ry());
    if(e->button() == Qt::LeftButton)//当鼠标左键按下
    {
        mousePressed = true;
        QVector<QPoint> line;
        line.append(e->pos());
        _lines.append(line);

        QColor lineColor = penColor;
        _lineColors.append(lineColor);

        int lineWidth = penWidth;
        _lineWidth.append(lineWidth);

        update();
    }
}
void FreeDrawing::mouseReleaseEvent(QMouseEvent *e) {
//    printf("mouseReleaseEvent e->pos(%d, %d) \n", e->pos().rx(), e->pos().ry());
    if(e->button() == Qt::LeftButton)//当鼠标左键按下
    {
        mousePressed = false;
        if(_lines.size() <= 0) {
            return;
        }
        QVector<QPoint>& lastLine = _lines.last();
        lastLine.append(e->pos());

        update();
    }
}
void FreeDrawing::mouseMoveEvent(QMouseEvent *e) {
//    printf("mouseMoveEvent e->pos(%d, %d) e->button():%d\n", e->pos().rx(), e->pos().ry(), e->button());
//    if(e->button() == Qt::LeftButton)//当鼠标左键按下
    if(mousePressed)
    {
        if(_lines.size() <= 0) {
            return;
        }
        QVector<QPoint>& lastLine = _lines.last();
        lastLine.append(e->pos());
        update();
    }
}

void FreeDrawing::resizeEvent(QResizeEvent *event) {

    if(event->size() == event->oldSize()) {
        printf("size is equal.");
        return;
    }
    printf("_pixmap: %d x %d", _pixmap.size().width(), _pixmap.size().height());
    printf("resizeEvent oldSize: %d x %d", event->oldSize().width(), event->oldSize().height());
    printf("resizeEvent size():  %d x %d", event->size().width(), event->size().height());
    QSize size = event->size();
//    _pixmap = _originPixmap.scaled(size, Qt::AspectRatioMode::IgnoreAspectRatio, Qt::SmoothTransformation);
//    printf("xx _pixmap: %d x %d", _pixmap.size().width(), _pixmap.size().height());
}
