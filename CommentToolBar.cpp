#include "CommentToolBar.h"
#include "ui_CommentToolBar.h"
#include <QLayout>
#include <QSpacerItem>
#include <QResizeEvent>
#include "common.h"


CommentToolBar::CommentToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentToolBar)
{
    ui->setupUi(this);

//    QHBoxLayout* hBoxLayout = new QHBoxLayout();

    int iconSize = 40 * Resolution::getInstance()->scaleX();

    ui->closeButton->setImages(QPixmap(":/images/res/images/close.png"), iconSize, iconSize);
    ui->rubberButton->setImages(QPixmap(":/images/res/images/rubber.png"), iconSize, iconSize);
    ui->whiteBoardButton->setImages(QPixmap(":/images/res/images/whiteboard.png"), iconSize, iconSize);

    iconSize = 20 * Resolution::getInstance()->scaleX();
    ui->redpenButton->setImages(QPixmap(":/images/res/images/redpen.png"), iconSize, iconSize);
    ui->whitepenButton->setImages(QPixmap(":/images/res/images/whitepen.png"), iconSize, iconSize);
    ui->blackpenButton->setImages(QPixmap(":/images/res/images/blackpen.png"), iconSize, iconSize);

    ui->pensize1->setImages(QPixmap(":/images/res/images/textsize1.png"), iconSize, iconSize);
    ui->pensize2->setImages(QPixmap(":/images/res/images/textsize2.png"), iconSize, iconSize);
    ui->pensize3->setImages(QPixmap(":/images/res/images/textsize3.png"), iconSize, iconSize);

//    redPenButton = new ImageButton(this);
//    redPenButton->setImages(QPixmap(":/images/res/images/redpen.png"), iconSize, iconSize);

//    ui->centerLayout->addStretch(1);
//    ui->centerLayout->addWidget(closeButton, 0, Qt::AlignHCenter | Qt::AlignBottom);
//    ui->centerLayout->addWidget(rubberButton, 0, Qt::AlignHCenter | Qt::AlignBottom);
//    ui->centerLayout->addWidget(whiteBoardButton, 0, Qt::AlignHCenter | Qt::AlignBottom);
//    ui->centerLayout->addStretch(1);



//    ui->leftLayout->addWidget(new QWidget(this));
//    ui->rightLayout->addWidget(new ImageButton(this));

//    whiteBoardButton = new ImageButton(this);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addStretch(1);
    layout->addWidget(ui->closeButton, 0, Qt::AlignHCenter | Qt::AlignBottom);
    layout->addWidget(ui->rubberButton, 0, Qt::AlignHCenter | Qt::AlignBottom);
    layout->addWidget(ui->whiteBoardButton, 0, Qt::AlignHCenter | Qt::AlignBottom);
    layout->addStretch(1);
    setLayout(layout);

//    QGridLayout* gridLayout = new QGridLayout(this);

//    gridLayout->

//    ui->rightContainer->setLayout(gridLayout);

//    layout()->addWidget(closeButton);

//    ui->close->setImages(QPixmap(":/images/res/images/close.png"));
//    ui->redPen->setImages(QPixmap(":/images/res/images/redPen.png"));
//    ui->blackPen->setImages(QPixmap(":/images/res/images/blackPen.png"));
//    ui->whitePen->setImages(QPixmap(":/images/res/images/whitePen.png"));
//    ui->rubber->setImages(QPixmap(":/images/res/images/rubber.png"));

//    printf("redPen size: %d x %d", ui->redPen->width(), ui->redPen->height());
//    connect(ui->close, &ImageButton::imageButtonclicked, this, &CommentToolBar::closeClicked);
//    connect(ui->close, SIGNAL(clicked()), this, SLOT(slotOfClose()));
//    connect(ui->redPen, SIGNAL(clicked()), this, SLOT(slotOfRedpen()));
//    connect(ui->blackPen, SIGNAL(clicked()), this, SLOT(slotOfBlackpen()));
//    connect(ui->whitePen, SIGNAL(clicked()), this, SLOT(slotOfWhitepen()));
//    connect(ui->rubber, SIGNAL(clicked()), this, SLOT(slotOfRubber()));

//    QPalette pal(palette());
//    pal.setColor(QPalette::Background, Qt::yellow); //设置背景黑色
//    setAutoFillBackground(true);
//    setPalette(pal);
}

CommentToolBar::~CommentToolBar()
{
    delete ui;
}

const QPushButton *CommentToolBar::closeButton() {
    return ui->closeButton;
}
const QPushButton *CommentToolBar::redPenButton() {
    return ui->redpenButton;
}
const QPushButton *CommentToolBar::whitePenButton(){
    return ui->whitepenButton;
}
const QPushButton *CommentToolBar::blackPenButton(){
    return ui->blackpenButton;
}
const QPushButton *CommentToolBar::rubberButton(){
    return ui->rubberButton;
}

const QPushButton *CommentToolBar::whiteboardButton(){
    return ui->whiteBoardButton;
}

const QPushButton *CommentToolBar::penSize1Button() {
    return ui->pensize1;
}
const QPushButton *CommentToolBar::penSize2Button() {
    return ui->pensize2;
}
const QPushButton *CommentToolBar::penSize3Button() {
    return ui->pensize3;
}

void CommentToolBar::resizeEvent(QResizeEvent *event) {
//    printf("resizeEvent oldSize: %d x %d", event->oldSize().width(), event->oldSize().height());
//    printf("resizeEvent: %d x %d", event->size().width(), event->size().height());
//    QRect rect = ui->gridWidget->geometry();
//    printf("resizeEvent: %d x %d x %d x %d", rect.x(), rect.y(), rect.width(), rect.height());

    int ax = event->size().width() - ui->gridWidget->width();
    int ay = event->size().height() - ui->gridWidget->height();

    ui->gridWidget->move(ax, ay);
//    rect.setX(rect.x() + 1);
//    redPenButton->setGeometry(rect);

//    layout->addWidget(ui->rightContainer, 0, Qt::AlignHCenter | Qt::AlignBottom);
}


