#include "navigator.h"
#include "ui_navigator.h"
#include "common.h"
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>

Navigator::Navigator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Navigator)
{
    ui->setupUi(this);

    items<<"video"<<"camera"<<"whiteboard";

    /*单选菜单效果*/
    buttonGround = new QButtonGroup();
    buttonGround->setExclusive(true);
    connect(buttonGround, SIGNAL(buttonToggled(int, bool)), this, SLOT(onButtonToggled(int, bool)));
    connect(buttonGround, SIGNAL(buttonToggled(int, bool)), this, SIGNAL(buttonToggled(int, bool)));

    QHBoxLayout *hLayout = new QHBoxLayout();
//    hLayout->setAlignment(Qt::AlignBottom);
    for(int i = 0; i < items.size(); i++) {
//        QPushButton *button = new QPushButton(items.at(i));
//        button->setFixedSize(80, 30);
        IconButton *button = new IconButton(tr(":/res/icons/%1_o.svg").arg(items.at(i)), tr(":/res/icons/%1.svg").arg(items.at(i)));
        button->setFixedSize(60, 60);
        button->setCheckable(true);
        buttonGround->addButton(button, i);
        hLayout->addSpacing(10);
        hLayout->addWidget(button);
        hLayout->addSpacing(10);
    }
    hLayout->addStretch();
    setLayout(hLayout);
}

Navigator::~Navigator()
{
    delete ui;
}


void Navigator::setChecked(int index) {
    buttonGround->button(index)->setChecked(true);
}

void Navigator::paintEvent(QPaintEvent *event) {
//    QPainter painter(this);

//    painter.setPen(QColor(200, 200, 200));
//    // 上面画线
//    painter.drawLine(0, 0, this->width() - 1, 0);
//    // 左面画线
//    painter.drawLine(0, 0, 0, this->height() - 1);
//    // 右侧画线
//    painter.drawLine(width() - 1, 0, width() - 1, this->height() - 1);
//    // 下面画线
//    painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
}

void Navigator::onButtonPressed(int index) {
//    printf("index: %d checked: %b", index, checked);
    printf("%s() index:%d", __FUNCTION__, index);
}

void Navigator::onButtonReleased(int index) {
//    printf("index: %d checked: %b", index, checked);
    printf("%s() index:%d", __FUNCTION__, index);
}

void Navigator::onButtonToggled(int index, bool checked) {
    printf("%s() index: %d checked: %d", __FUNCTION__, index, checked);
}
