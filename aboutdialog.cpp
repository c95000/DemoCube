#include "aboutdialog.h"
#include <QLabel>
#include "common.h"
#include <QPushButton>
#include "activatewidget.h"
#include "Configure.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("关于软件"));
//    setFixedSize(310, 240);

//    setStyleSheet("QLabel{text-align:center; color:#ff6600;}");
//    setStyleSheet("QLabel{color:#ff6600;}");

    software = new QLabel("实训优学v1.0");
    QFont font1 = software->font();
    font1.setPointSize(17);
    software->setFont(font1);
    software->setAlignment(Qt::AlignCenter);

    company = new QLabel("深圳市捷宜电子");
    QFont font = company->font();
    font.setPointSize(13);
    company->setFont(font);
    company->setAlignment(Qt::AlignCenter);

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(new QPushButton("确定"), QDialogButtonBox::AcceptRole);
    connect(buttonBox, &QDialogButtonBox::accepted, [=](){
        emit accept();
    });

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignHCenter);

    ActivateWidget* activateWidget = new ActivateWidget();
//    QLabel *deviceId = new QLabel("this");
//    deviceId->setAlignment(Qt::AlignCenter);


    vLayout->addStretch();
    vLayout->addWidget(software);
    vLayout->addSpacing(15);
    vLayout->addWidget(company);
    vLayout->addSpacing(15);
    if(!Configure::getInstance()->isLicensed()) {
        vLayout->addWidget(activateWidget);
    }
    vLayout->addStretch();
    vLayout->addWidget(buttonBox);

    setLayout(vLayout);
}

AboutDialog::~AboutDialog() {
    printf("%s() is called", __FUNCTION__);
    delete company;
    delete software;
}
