#include "assist.h"
#include <QStyleOption>
#include <QPainter>
#include <QDialog>
#include "SettingDialog.h"
#include "aboutdialog.h"

Assist::Assist(QWidget *parent) : QWidget(parent)
{

    QHBoxLayout *hLayout = new QHBoxLayout();

    btnSetting = new IconButton(tr("设置"), tr(":res/icons/setting_o.svg"), tr(":res/icons/setting.svg"));
    btnHelp = new IconButton(tr("帮助"), tr(":res/icons/help_o.svg"), tr(":res/icons/help.svg"));

    hLayout->addStretch();
    hLayout->addSpacing(10);
    hLayout->addWidget(btnSetting);
    hLayout->addSpacing(20);
    hLayout->addWidget(btnHelp);
    hLayout->addSpacing(10);
    hLayout->addStretch();
    setLayout(hLayout);

    QString styleSheet = this->styleSheet();
    styleSheet += "Assist{border-radius:10px;border:1px solid #aaaaaa;}";
    setStyleSheet(styleSheet);


    connect(btnSetting, &QPushButton::clicked, [=]() {
        printf("onSettingButtonClicked");
        SettingDialog *dlg=new SettingDialog(this);

        int ret = dlg->exec();
        if(ret==QDialog::Accepted) {
            printf("!ret:%d", ret);
        } else {
            printf("ret:%d", ret);
        }
        delete dlg;
    });

    connect(btnHelp, &QPushButton::clicked, [=]() {
        printf("onSettingButtonClicked");
        AboutDialog *dlg=new AboutDialog(this);

        int ret = dlg->exec();
        if(ret==QDialog::Accepted) {
            printf("!ret:%d", ret);
        } else {
            printf("ret:%d", ret);
        }
        delete dlg;
    });
}

void Assist::paintEvent(QPaintEvent *) {
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
