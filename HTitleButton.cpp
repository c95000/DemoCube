#include "HTitleButton.h"
#include "ui_HTitleButton.h"

HTitleButton::HTitleButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HTitleButton)
{
    ui->setupUi(this);
}

HTitleButton::~HTitleButton()
{
    delete ui;
}


void HTitleButton::setText(const QString &text) {
    ui->label->setText(text);
}
