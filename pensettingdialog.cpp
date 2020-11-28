#include "pensettingdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include "common.h"

PenSettingDialog::PenSettingDialog(QWidget *parent) : QDialog(parent)
{
    penColor = Qt::red;
    penWidth = 4;
    init();
}

PenSettingDialog::PenSettingDialog(const QColor& color, const int width, QWidget *parent): QDialog(parent), penColor(color), penWidth(width) {
    init();
}

void PenSettingDialog::init() {
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("线条属性"));
    setFixedSize(310, 240);


    QLabel *lineColorLabel = new QLabel("颜色:");
    QList<QColor> colorList = Configure::getInstance()->getPenColors();
//    colorList<<Qt::red<<Qt::green<<Qt::blue<<Qt::black;


    /*单选菜单效果*/
    QButtonGroup *colorButtonGroup = new QButtonGroup();
    colorButtonGroup->setExclusive(true);

    QHBoxLayout *colorLayout = new QHBoxLayout();
    colorLayout->addWidget(lineColorLabel);
    for(int i = 0; i < colorList.size(); i++) {
        PenState *button = new PenState(colorList.at(i));
        button->setCheckable(true);
        colorButtonGroup->addButton(button, i);
        colorLayout->addWidget(button);
        if(colorList.at(i) == penColor) {
            button->setChecked(true);
        }
    }


    QLabel *lineWidthLabel = new QLabel("粗细:");
    QList<int> widthList = Configure::getInstance()->getPenWidths();
//    widthList<<4<<7<<10<<13;


    /*单选菜单效果*/
    QButtonGroup *widthButtonGroup = new QButtonGroup();
    widthButtonGroup->setExclusive(true);

    QHBoxLayout *widthLayout = new QHBoxLayout();
    widthLayout->addWidget(lineWidthLabel);
    for(int i = 0; i < widthList.size(); i++) {
        PenState *button = new PenState(widthList.at(i));
        button->setCheckable(true);
        widthButtonGroup->addButton(button, i);
        widthLayout->addWidget(button);
        if(widthList.at(i) == penWidth) {
            button->setChecked(true);
        }
    }


    QDialogButtonBox *buttonBox = new QDialogButtonBox();
    buttonBox->addButton(new QPushButton("确定"), QDialogButtonBox::AcceptRole);
    buttonBox->addButton(new QPushButton("取消"), QDialogButtonBox::RejectRole);
    connect(buttonBox, &QDialogButtonBox::accepted, [=](){
        printf("accepted");
        emit accept();
    });

    connect(buttonBox, &QDialogButtonBox::rejected, [=](){
        printf("rejected");
        emit reject();
    });

    QVBoxLayout *vLayout = new QVBoxLayout();
//    vLayout->setAlignment(Qt::AlignHCenter);

    vLayout->addStretch();
    vLayout->addLayout(colorLayout, 1);
    vLayout->addLayout(widthLayout, 1);
    vLayout->addStretch();
    vLayout->addWidget(buttonBox);
    setLayout(vLayout);


    connect(colorButtonGroup, SIGNAL(buttonToggled(int, bool)), this, SLOT(onColorSelected(int, bool)));
    connect(widthButtonGroup, SIGNAL(buttonToggled(int, bool)), this, SLOT(onWidthSelected(int, bool)));

}

void PenSettingDialog::onColorSelected(int index, bool checked) {
    printf("%s index: %d checked: %d", __FUNCTION__, index, checked);
    if(checked) {
        penColor = Configure::getInstance()->colorByIndex(index);
    }
}

void PenSettingDialog::onWidthSelected(int index, bool checked) {
    printf("%s index: %d checked: %d", __FUNCTION__, index, checked);
    if(checked) {
        penWidth = Configure::getInstance()->widthByIndex(index);
    }
}

QColor PenSettingDialog::getColor() const {
    return penColor;
}

int PenSettingDialog::getWidth() const {
    return penWidth;
}
