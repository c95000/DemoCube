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

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white); //设置背景黑色
    setAutoFillBackground(true);
    setPalette(pal);

//    freeDrawingMenu = new FreeDrawingMenu();
//    QHBoxLayout *hLayout = new QHBoxLayout();
//    hLayout->addStretch();
//    hLayout->addWidget(freeDrawingMenu, 0, Qt::AlignBottom);
//    setLayout(hLayout);

//    connect(freeDrawingMenu, &FreeDrawingMenu::penChanged, this, &FreeDrawing::on_penChanged);
//    connect(freeDrawingMenu, &FreeDrawingMenu::signalUndo, this, &FreeDrawing::on_undo);
//    connect(freeDrawingMenu, &FreeDrawingMenu::signalClose, this, &FreeDrawing::on_close);
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

void FreeDrawing::clear(const QPixmap& background) {
    _originPixmap = background.copy();
    for(int i = 0; i < _lines.size(); i++) {
        _lines[i].clear();
    }

    _lines.clear();
    _lineWidth.clear();
    _lineColors.clear();
    update();
}

void FreeDrawing::on_colorChanged(int index) {
    penColor = Configure::getInstance()->colorByIndex(index);
}

void FreeDrawing::on_widthChanged(int index) {
    penWidth = Configure::getInstance()->widthByIndex(index);
}

void FreeDrawing::on_btnUndo() {
    if(_lines.size() > 0) {
        _lines.takeLast().clear();
        _lineWidth.removeLast();
        _lineColors.removeLast();
        update();
    }
}

void FreeDrawing::on_btnClear() {
    clear();
}

void FreeDrawing::on_btnClose() {
    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".png";
    printf("filename: %s", fileName.toStdString().c_str());
    if (fileName.length() > 0)
    {
//        freeDrawingMenu->hide();//不包含工具栏
        QPixmap pixmap = grab();
//        freeDrawingMenu->show();
        pixmap.save(fileName);
    }
}

void FreeDrawing::paintEvent(QPaintEvent *) {
//    QPixmap pixmap(size());
//    pixmap.fill(Qt::white);

    QPainter painter;//将_pixmap作为画布
    painter.begin(this);
    painter.drawPixmap(0, 0, _pixmap);

//    painter.drawPixmap(0, 0, pixmap);//将pixmap画到窗体
//    if(_originPixmap.width() > 0 && _originPixmap.height() > 0) {
//        double ratio = 1.0 * _originPixmap.width() / _originPixmap.height();
//        double viewRatio = 1.0 * width()/height();

//        QRect rect;

//        if(ratio > viewRatio) {
//            int w = width();
//            int h = width() / ratio;
//            int offsetX = 0;
//            int offsetY = (height() - h) / 2;
//            rect.setWidth(w);
//            rect.setHeight(h);
//            rect.moveTo(offsetX, offsetY);
//        } else {
//            int w = height() * ratio;
//            int h = height();
//            int offsetX = (width() - w) / 2;
//            int offsetY = 0;
//            rect.setWidth(w);
//            rect.setHeight(h);
//            rect.moveTo(offsetX, offsetY);
//        }

//        painter.drawPixmap(rect , _originPixmap);//将pixmap画到窗体
//    }

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
}

void FreeDrawing::showEvent(QShowEvent *event) {
    QPainter painter;//将_pixmap作为画布
    painter.begin(&_pixmap);
    painter.drawPixmap(10, 10, _originPixmap);
    painter.end();
    _originPixmap = QPixmap();
}

void FreeDrawing::hideEvent(QHideEvent *event) {

}
