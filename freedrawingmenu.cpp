#include "freedrawingmenu.h"
#include "ui_freedrawingmenu.h"
#include <QHBoxLayout>
#include <QtWidgets/QComboBox>
#include "common.h"
#include "linestate.h"


FreeDrawingMenu::FreeDrawingMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FreeDrawingMenu)
{
    ui->setupUi(this);
    colorCombo = new QComboBox();
    QStringList colorList;
    colorList<<"红色"<<"绿色"<<"蓝色"<<"黄色";
    colorCombo->addItems(colorList);
    connect(colorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_color_changed(int)));

    widthCombo = new QComboBox();
    QStringList weightList;
    weightList<<"一号"<<"二号"<<"三号"<<"四号";
    widthCombo->addItems(weightList);
    connect(widthCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_width_changed(int)));

    lineState = new LineState();

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(colorCombo);
    hLayout->addWidget(widthCombo);
    hLayout->addWidget(lineState);
    hLayout->addStretch();

    setLayout(hLayout);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumWidth(0);
    setMinimumHeight(0);

    on_color_changed(colorCombo->currentIndex());
    on_width_changed(widthCombo->currentIndex());

}

FreeDrawingMenu::~FreeDrawingMenu()
{
    delete ui;
}

void FreeDrawingMenu::resizeEvent(QResizeEvent *event) {
    printf("colorCombo: %d x %d", colorCombo->width(), colorCombo->height());
    printf("widthCombo: %d x %d", widthCombo->width(), widthCombo->height());
//    printf("lineState: %d x %d", lineState->width(), lineState->height());
    lineState->setFixedSize(widthCombo->width(), widthCombo->height());
    update();
}

QColor& FreeDrawingMenu::getPenColor() {
    return penColor;
}

int FreeDrawingMenu::getPenWidth() {
    return penWidth;
}

void FreeDrawingMenu::on_color_changed(int index) {
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

    lineState->setColor(color);
    penColor = color;
    emit penChanged();
}

void FreeDrawingMenu::on_width_changed(int index) {

    int width = 3;
    switch (index) {
    case 0:
        width = 3;
        break;
    case 1:
        width = 5;
        break;
    case 2:
        width = 7;
        break;
    case 3:
        width = 9;
        break;
    }

    lineState->setWidth(width);
    penWidth = width;
    emit penChanged();
}
