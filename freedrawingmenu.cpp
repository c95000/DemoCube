#include "freedrawingmenu.h"
#include "ui_freedrawingmenu.h"
#include <QHBoxLayout>
#include <QtWidgets/QComboBox>
#include "common.h"
#include "linestate.h"
#include <QPushButton>

FreeDrawingMenu::FreeDrawingMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FreeDrawingMenu)
{
    ui->setupUi(this);
    colorCombo = new QComboBox();
    QStringList colorList;
    colorList<<" 红色"<<" 绿色"<<" 蓝色"<<" 黄色";
    colorCombo->addItems(colorList);

    widthCombo = new QComboBox();
    QStringList weightList;
    weightList<<" 一号"<<" 二号"<<" 三号"<<" 四号";
    widthCombo->addItems(weightList);

    lineState = new LineState();
    btnUndo = new QPushButton("撤销");
    btnClear = new QPushButton("清除");
    btnClose = new QPushButton("保存");

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(colorCombo);
    hLayout->addWidget(widthCombo);
    hLayout->addWidget(lineState);
    hLayout->addWidget(btnUndo);
    hLayout->addWidget(btnClear);
    hLayout->addWidget(btnClose);
    hLayout->addStretch();

    setLayout(hLayout);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumWidth(0);
    setMinimumHeight(0);

    connect(colorCombo, SIGNAL(activated(int)), this, SLOT(on_colorChanged(int)));
    connect(widthCombo, SIGNAL(activated(int)), this, SLOT(on_widthChanged(int)));


    connect(colorCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(signalColorChanged(int)));
    connect(widthCombo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(signalWidthChanged(int)));
    connect(btnUndo, SIGNAL(clicked(bool)), this, SIGNAL(signalUndo()));
    connect(btnClear, SIGNAL(clicked(bool)), this, SIGNAL(signalClear()));
    connect(btnClose, SIGNAL(clicked(bool)), this, SIGNAL(signalClose()));


//    on_colorChanged(colorCombo->currentIndex());
//    on_widthChanged(widthCombo->currentIndex());

    colorCombo->activated(0);
    widthCombo->activated(0);
}

FreeDrawingMenu::~FreeDrawingMenu()
{
    delete ui;
}

void FreeDrawingMenu::resizeEvent(QResizeEvent *event) {
//    printf("colorCombo: %d x %d", colorCombo->width(), colorCombo->height());
//    printf("widthCombo: %d x %d", widthCombo->width(), widthCombo->height());
//    printf("lineState: %d x %d", lineState->width(), lineState->height());

//    lineState->setFixedSize(widthCombo->width(), widthCombo->height());
//    btnUndo->setFixedSize(widthCombo->width(), widthCombo->height());
//    btnClose->setFixedSize(widthCombo->width(), widthCombo->height());


    QSize size = Configure::getInstance()->buttonSize();

    colorCombo->setFixedSize(size);
    widthCombo->setFixedSize(size);
    lineState->setFixedSize(size);
    btnUndo->setFixedSize(size);
    btnClear->setFixedSize(size);
    btnClose->setFixedSize(size);
}

QColor& FreeDrawingMenu::getPenColor() {
    return penColor;
}

int FreeDrawingMenu::getPenWidth() {
    return penWidth;
}

void FreeDrawingMenu::on_colorChanged(int index) {
    printf("index: %d", index);
//    <<"红色"<<"绿色"<<"蓝色"<<"黄色";

    QColor color = Qt::black;
    switch (index) {
    case 0:
        color = Qt::red;
        break;
    case 1:
        color = Qt::green;
        break;
    case 2:
        color = Qt::blue;
        break;
    case 3:
        color = Qt::yellow;
        break;
    }

    lineState->setLineColor(color);
    penColor = color;
//    emit signalColorChanged(index);
}

void FreeDrawingMenu::on_widthChanged(int index) {

    int width = 2;
    switch (index) {
    case 0:
        width = 2;
        break;
    case 1:
        width = 4;
        break;
    case 2:
        width = 6;
        break;
    case 3:
        width = 8;
        break;
    }

    lineState->setLineWidth(width);
    penWidth = width;
//    emit signalWidthChanged(index);
}

void FreeDrawingMenu::on_btnUndo() {
    printf("FreeDrawingMenu:: on_btnUndo");
    emit signalUndo();
}

void FreeDrawingMenu::on_btnClear() {
    printf("FreeDrawingMenu:: on_btnUndo");
    emit signalClear();
}

void FreeDrawingMenu::on_btnClose() {
    printf("FreeDrawingMenu:: on_btnClose");
    emit signalClose();
}
