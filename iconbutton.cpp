#include "iconbutton.h"
#include <QIcon>
#include <QBitmap>
#include <QtSvg/QSvgRenderer>
#include <QDomDocument>

IconButton::IconButton(QWidget *parent) : QToolButton(parent) {
    QString styleSheet = this->styleSheet();
    styleSheet += "QToolButton{border-style:flat}";
    styleSheet += "QToolButton:hover{border:2px solid black;border-radius:5px}";
    setStyleSheet(styleSheet);

    setFixedSize(60, 60);
}

IconButton::IconButton(const QString& defaultIconRes, const QString& activeIconRes, QWidget *parent) : QToolButton(parent)
{
//    QIcon icon1;
//    icon1.addFile(":/res/icons/account_circle_outline.svg");

//    QIcon icon2;
//    icon2.addFile(":/res/icons/account_circle.svg");



//    QPixmap pixmap(defaultIcon);
//    QBitmap mask = pixmap.createMaskFromColor(QColor('black'), Qt::MaskOutColor);
//    pixmap.fill((QColor('red')));
//    pixmap.setMask(mask);


//    QIcon icon1(defaultIcon);
//    QIcon icon2(activeIcon);
//    this->setIcon(icon1);

    defaultIcon = QIcon(defaultIconRes);
    activateIcon = QIcon(activeIconRes);
    this->setIcon(defaultIcon);


    QString styleSheet = this->styleSheet();
    styleSheet += "QToolButton{border-style:flat}";
    styleSheet += "QToolButton:hover{border:2px solid black;border-radius:5px}";
    setStyleSheet(styleSheet);

    setFixedSize(60, 60);


//    QString styleSheet = this->styleSheet();
//    styleSheet += "QLabel{text-align:center; color:#ff6600;}";
//    styleSheet += "QToolButton{background-image: url(\":/res/images/add1.png\");background-repeat: no-repeat;background-position: center;border-style:flat}"
//                  "QToolButton:hover{background-image: url(\":/res/images/add2.png\");}"
//                  "QToolButton:pressed{background-image: url(\":/res/images/add2.png\");}";

//    styleSheet += "QToolButton{border-image: url(:/res/images/add1.png);}"
//                  "QToolButton:hover{border-image: url(\":/res/images/add2.png\");}"
//                  "QToolButton:pressed{border-image: url(\":/res/images/close.png\");}";

//    styleSheet += tr("QToolButton{qproperty-icon: url(:/res/icons/account_circle_outline.svg);}"
//                     "QToolButton:hover{qproperty-icon: url(:/res/icons/account_circle.svg);}"
//                     "QToolButton:pressed{qproperty-icon: url(:/res/icons/account_circle.svg);}");

//    setStyleSheet(styleSheet);



//    QSvgRenderer m_svgRender;
//    m_svgRender.load(QString(":/res/icons/account_circle.svg"));

//    QPalette pal(palette());
//    pal.setColor(QPalette::Background, Qt::yellow); //设置背景黑色
//    setAutoFillBackground(true);
//    setPalette(pal);
//    setStyleSheet(QString("background-color:%1").arg(Qt::red));
//    setAutoFillBackground(true);


//    QString style = styleSheet();
//    style += "QPushButton{border-image: url(:/res/icons/account_circle.svg)}";
//    setStyleSheet(style);
    connect(this, &QPushButton::pressed, [=](){
        printf("pressed");
//        this->setIcon(icon2);
    }
    );
    connect(this, &QPushButton::released, [=](){
        printf("released");
//        this->setIcon(icon1);
    }
    );
//    connect(this, &QPushButton::clicked, [=](){
//        printf("clicked");
//    }
//    );
    connect(this, &QPushButton::toggled, [=](bool checked){
        printf("toggled %d", checked);
        if(checked) {
            setIcon(activateIcon);
        } else {
            setIcon(defaultIcon);
        }
    }
    );
}


void IconButton::resizeEvent(QResizeEvent *event) {
    this->setIconSize(event->size());
//    QSvgRenderer m_svgRender;
//    m_svgRender.load(QString(":/res/icons/account_circle.svg"));
//    QPixmap *pixmap = new QPixmap(event->size());
//    pixmap->fill(Qt::transparent);
//    QPainter painter(pixmap);
//    m_svgRender.render(&painter);
//    QIcon ico(*pixmap);
//    setIcon(ico);
}

void IconButton::paintEvent(QPaintEvent *e) {
    QToolButton::paintEvent(e);

    // can draw title of the button here
//    QPainter painter(this);
//    painter.drawLine(0, 0, 20, 20);
//    painter.end();

//    QPainter qPainter(this);
//    QSvgRenderer m_svgRender;
//    m_svgRender.load(QString(":/res/icons/account_circle_outline.svg"));
//    m_svgRender.render(&qPainter ,QRectF(0,0,this->size().width() ,this->size().height()));
}

void IconButton::enterEvent(QEvent *event) {
    if(isCheckable()) {
    } else if(isEnabled()) {
        this->setIcon(activateIcon);
    }
}
void IconButton::leaveEvent(QEvent *event) {
    if(isCheckable()) {
    } else if(isEnabled()) {
        this->setIcon(defaultIcon);
    }
}
