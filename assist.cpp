#include "assist.h"
#include <QStyleOption>
#include <QPainter>

Assist::Assist(QWidget *parent) : QWidget(parent)
{

    QHBoxLayout *hLayout = new QHBoxLayout();

    btnSetting = new IconButton(tr(":res/icons/setting_o.svg"), tr(":res/icons/setting.svg"));
    btnHelp = new IconButton(tr(":res/icons/help_o.svg"), tr(":res/icons/help.svg"));

    hLayout->addStretch();
    hLayout->addSpacing(10);
    hLayout->addWidget(btnSetting);
    hLayout->addSpacing(20);
    hLayout->addWidget(btnHelp);
    hLayout->addSpacing(10);
    hLayout->addStretch();
    setLayout(hLayout);

    QString styleSheet = this->styleSheet();
    styleSheet += "border-radius:10px;border:1px solid #aaaaaa;";
    setStyleSheet(styleSheet);
}

void Assist::paintEvent(QPaintEvent *) {
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
