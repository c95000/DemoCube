#include "HTitleButton.h"
#include "ui_HTitleButton.h"

HTitleButton::HTitleButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HTitleButton)
{
    ui->setupUi(this);
    setStyleSheet("color:white;");
}

HTitleButton::~HTitleButton()
{
    delete ui;
}


void HTitleButton::setText(const QString &text) {
    ui->label->setText(text);
}


ImageButton *HTitleButton::imageButton() {
    return ui->button;
}

QPushButton *HTitleButton::button() {
    return ui->button;
}
