#include "CommentToolBar.h"
#include "ui_CommentToolBar.h"
#include <QLayout>
#include <QSpacerItem>
#include "common.h"

#include "common.h"

CommentToolBar::CommentToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentToolBar)
{
    ui->setupUi(this);

    QHBoxLayout* hBoxLayout = new QHBoxLayout();



    closeButton = new ImageButton(this);
    closeButton->setImages(QPixmap(":/images/res/images/close.png"), 40, 40);
    rubberButton = new ImageButton(this);
    rubberButton->setImages(QPixmap(":/images/res/images/rubber.png"), 40, 40);
    whiteBoardButton = new ImageButton(this);
    whiteBoardButton->setImages(QPixmap(":/images/res/images/whiteboard.png"), 40, 40);


//    ui->horizontalLayout_2->setStretch(0, 1);
//    ui->horizontalLayout_2->setStretch(1, 1);
//    ui->horizontalLayout_2->setStretch(2, 1);

//    ui->horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
    ui->centerLayout->addStretch();
    ui->centerLayout->addWidget(closeButton, 0, Qt::AlignHCenter | Qt::AlignBottom);
    ui->centerLayout->addWidget(rubberButton, 0, Qt::AlignHCenter | Qt::AlignBottom);
    ui->centerLayout->addWidget(whiteBoardButton, 0, Qt::AlignHCenter | Qt::AlignBottom);
    ui->centerLayout->addStretch();
    ui->centerLayout->setSizeConstraint(QLayout::SetNoConstraint);


    ui->leftLayout->addWidget(new QWidget(this));
    ui->rightLayout->addWidget(new ImageButton(this));

//    whiteBoardButton = new ImageButton(this);

//    QHBoxLayout* layout = new QHBoxLayout();
//    layout->addWidget(closeButton);
//    layout->addWidget(rubberButton);
////    layout->addWidget(whiteBoardButton);
//    setLayout(layout);

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

//const QPushButton *CommentToolBar::closeButton() {
//    return ui->close;
//}
//const QPushButton *CommentToolBar::redPenButton() {
//    return ui->redPen;
//}
//const QPushButton *CommentToolBar::whitePenButton(){
//    return ui->whitePen;
//}
//const QPushButton *CommentToolBar::blackPenButton(){
//    return ui->blackPen;
//}
//const QPushButton *CommentToolBar::rubberButton(){
//    return ui->rubber;
//}


