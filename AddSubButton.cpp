#include "AddSubButton.h"
#include "ui_AddSubButton.h"

AddSubButton::AddSubButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddSubButton)
{
    maxValue = 9;
    currentValue = 5;
    ui->setupUi(this);
//    ui->value->setNum(currentValue);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(255, 120, 0)); //设置背景黑色
    setAutoFillBackground(true);
    setPalette(pal);

//    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
//    setFixedSize(100,100);

//    connect(ui->addButton, &QPushButton::clicked, this, &AddSubButton::on_btnAdd_clicked);
//    connect(ui->subButton, &QPushButton::clicked, this, &AddSubButton::on_btnSub_clicked);
}

AddSubButton::~AddSubButton()
{
    delete ui;
}

void AddSubButton::on_btnAdd_clicked() {
    currentValue ++;
    if(currentValue > maxValue) {
        currentValue = maxValue;
    }
//    ui->value->setText(QString::number(currentValue));
//    ui->value->setNum(currentValue);
}

void AddSubButton::on_btnSub_clicked() {
    currentValue--;
    if(currentValue < 0) {
        currentValue = 0;
    }
//    ui->value->setText(QString::number(currentValue));
//    ui->value->setNum(currentValue);
}

void AddSubButton::setText(const QString &text) {
    ui->value->setText(text);
}
