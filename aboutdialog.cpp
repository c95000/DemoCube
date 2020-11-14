#include "aboutdialog.h"
#include <QLabel>
#include "common.h"
#include <QPushButton>

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
    printf("%s() is called", __FUNCTION__);
    setWindowTitle(tr("关于软件"));
    resize(280, 240);

//    setStyleSheet("QLabel{text-align:center; color:#ff6600;}");
//    setStyleSheet("QLabel{color:#ff6600;}");

    software = new QLabel("实训优学v1.0");
    QFont font1 = software->font();
    font1.setPointSize(14);
    software->setFont(font1);
    software->setAlignment(Qt::AlignCenter);

    company = new QLabel("深圳市捷宜电子");
    QFont font = company->font();
    font.setPointSize(16);
    company->setFont(font);
    company->setAlignment(Qt::AlignCenter);

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(new QPushButton("确定"), QDialogButtonBox::AcceptRole);
    connect(buttonBox, &QDialogButtonBox::accepted, [=](){
        printf("tests");
        emit accept();
    });

    QVBoxLayout *vLayout = new QVBoxLayout();
//    vLayout->setAlignment(Qt::AlignHCenter);

    vLayout->addStretch();
    vLayout->addWidget(software);
    vLayout->addSpacing(15);
    vLayout->addWidget(company);
    vLayout->addSpacing(40);
    vLayout->addWidget(buttonBox);
    vLayout->addSpacing(25);

    setLayout(vLayout);
}

AboutDialog::~AboutDialog() {
    printf("%s() is called", __FUNCTION__);
    delete company;
    delete software;
}
