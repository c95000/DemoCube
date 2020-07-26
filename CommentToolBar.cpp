#include "CommentToolBar.h"
#include "ui_CommentToolBar.h"

#include "common.h"

CommentToolBar::CommentToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentToolBar)
{
    ui->setupUi(this);

    ui->close->setImages(QPixmap(":/images/res/images/close.png"));
    ui->redPen->setImages(QPixmap(":/images/res/images/redPen.png"));
    ui->blackPen->setImages(QPixmap(":/images/res/images/blackPen.png"));
    ui->whitePen->setImages(QPixmap(":/images/res/images/whitePen.png"));
    ui->rubber->setImages(QPixmap(":/images/res/images/rubber.png"));

    printf("redPen size: %d x %d", ui->redPen->width(), ui->redPen->height());
//    connect(ui->close, &ImageButton::imageButtonclicked, this, &CommentToolBar::closeClicked);
//    connect(ui->close, SIGNAL(clicked()), this, SLOT(slotOfClose()));
//    connect(ui->redPen, SIGNAL(clicked()), this, SLOT(slotOfRedpen()));
//    connect(ui->blackPen, SIGNAL(clicked()), this, SLOT(slotOfBlackpen()));
//    connect(ui->whitePen, SIGNAL(clicked()), this, SLOT(slotOfWhitepen()));
//    connect(ui->rubber, SIGNAL(clicked()), this, SLOT(slotOfRubber()));

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::yellow); //设置背景黑色
    setAutoFillBackground(true);
    setPalette(pal);
}

CommentToolBar::~CommentToolBar()
{
    delete ui;
}

const QPushButton *CommentToolBar::closeButton() {
    return ui->close;
}
const QPushButton *CommentToolBar::redPenButton() {
    return ui->redPen;
}
const QPushButton *CommentToolBar::whitePenButton(){
    return ui->whitePen;
}
const QPushButton *CommentToolBar::blackPenButton(){
    return ui->blackPen;
}
const QPushButton *CommentToolBar::rubberButton(){
    return ui->rubber;
}

void CommentToolBar::slotOfClose()
{
    printf("closeClicked");
//    emit signalOfEvent(CommentToolBarEvent::Close);
    emit test();
}

void CommentToolBar::slotOfRedpen()
{
    printf("slotOfRedpen");
    emit signalOfEvent(CommentToolBarEvent::Redpen);
}
void CommentToolBar::slotOfBlackpen()
{
    printf("slotOfBlackpen");
    emit signalOfEvent(CommentToolBarEvent::Blackpen);
}

void CommentToolBar::slotOfWhitepen()
{
    printf("slotOfWhitepen");
    emit signalOfEvent(CommentToolBarEvent::Whitepen);
}

void CommentToolBar::slotOfRubber()
{
    printf("slotOfRubber");
    emit signalOfEvent(CommentToolBarEvent::Rubber);
}

