#include "iconbuton.h"
#include <QIcon>
#include <QBitmap>
#include <QtSvg/QSvgRenderer>
#include <QDomDocument>

void SetAttrRecur(QDomElement &elem, QString strtagname, QString strattr, QString strattrval);


void SetAttrRecur(QDomElement &elem, QString strtagname, QString strattr, QString strattrval)
{
    // if it has the tagname then overwritte desired attribute
    if (elem.tagName().compare(strtagname) == 0)
    {
        elem.setAttribute(strattr, strattrval);
    }
    // loop all children
    for (int i = 0; i < elem.childNodes().count(); i++)
    {
        if (!elem.childNodes().at(i).isElement())
        {
            continue;
        }
//        SetAttrRecur(elem.childNodes().at(i).toElement(), strtagname, strattr, strattrval);
    }
}


IconButon::IconButon(const QString& defaultIcon, const QString& activeIcon, QWidget *parent) : QToolButton(parent)
{
//    QIcon icon1;
//    icon1.addFile(":/res/icons/account_circle_outline.svg");

//    QIcon icon2;
//    icon2.addFile(":/res/icons/account_circle.svg");



//    QPixmap pixmap(defaultIcon);
//    QBitmap mask = pixmap.createMaskFromColor(QColor('black'), Qt::MaskOutColor);
//    pixmap.fill((QColor('red')));
//    pixmap.setMask(mask);


    QIcon icon1(defaultIcon);
    QIcon icon2(activeIcon);
    this->setIcon(icon1);
    setFixedSize(100, 100);
    setStyleSheet("border-style:flat");  //设置透明的

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
        this->setIcon(icon2);
    }
    );
    connect(this, &QPushButton::released, [=](){
        printf("released");
        this->setIcon(icon1);
    }
    );
    connect(this, &QPushButton::clicked, [=](){
        printf("clicked");
    }
    );
}


void IconButon::resizeEvent(QResizeEvent *event) {
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

void IconButon::paintEvent(QPaintEvent *e) {
    QToolButton::paintEvent(e);
//    QPainter qPainter(this);
//    QSvgRenderer m_svgRender;
//    m_svgRender.load(QString(":/res/icons/account_circle_outline.svg"));
//    m_svgRender.render(&qPainter ,QRectF(0,0,this->size().width() ,this->size().height()));
}
