#include "TitleButton.h"
#include "ui_TitleButton.h"
#include "Configure.h"
#include "common.h"

TitleButton::TitleButton(QWidget *parent) :
    QWidget(parent),ui(new Ui::TitleButton)
{
    ui->setupUi(this);

    setStyleSheet("color:white;");

//    printf("TitleButton x:%d y:%d l:%d t:%d r:%d b:%d w:%d h:%d", this->geometry().x(), this->geometry().y(),
//           this->geometry().left(), this->geometry().top(), this->geometry().right(), this->geometry().bottom(),
//           this->geometry().width(), this->geometry().height());

//    ui->label->setStyleSheet ("background-color: rgb(255, 0, 0);");
//    ui->label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    ui->pushButton->setStyleSheet("background-color: rgb(255, 0, 0);");

    ui->verticalLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

//    setAutoFillBackground(true);
//    setStyleSheet ("background-color: rgb(255, 255, 0);");
//    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
//    setFixedSize(80, 0);
}

TitleButton::~TitleButton()
{
    delete ui;
}

void TitleButton::setText(const QString &text) {
    ui->label->setText(text);
}

void TitleButton::setImages(const QPixmap &pixmaps) {
    ui->button->setImages(pixmaps);
}

QString TitleButton::text() const {
    return ui->label->text();
}

const QPushButton *TitleButton::pushButton() {
    return ui->button;
}

ImageButton *TitleButton::imageButton() {
    return ui->button;
}
