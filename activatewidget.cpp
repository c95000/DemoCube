#include "activatewidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include "deviceinfo.h"
#include "Configure.h"
#include "common.h"

ActivateWidget::ActivateWidget(QWidget *parent) : QWidget(parent)
{
    QLabel *deviceIdLabel, *deviceId;
    deviceIdLabel = new QLabel(this);
    deviceIdLabel->setText(tr("设备号:"));
    deviceId = new QLabel(this);
    deviceId->setText(getDeviceInfo());
    deviceId->setWordWrap(true);

    QPushButton *btnCopy;
    btnCopy = new QPushButton(this);
    btnCopy->setText(tr("复制"));


    QLabel *activateCodeLabel;
    activateCodeLabel = new QLabel(this);
    activateCodeLabel->setText(tr("激活码:"));
    QLineEdit *activateCode;
    activateCode = new QLineEdit(this);
//    activateCode->setText(caculateChecksum(deviceId->text()));

    QPushButton *btnActivate;
    btnActivate = new QPushButton(this);
    btnActivate->setText(tr("激活"));

    QGridLayout *pg=new QGridLayout;
    pg->addWidget(deviceIdLabel,0,0,1,1);
    pg->addWidget(deviceId,0,1,1,1);
    pg->addWidget(btnCopy,0,2,1,1);

    pg->addWidget(activateCodeLabel,1,0,1,1);
    pg->addWidget(activateCode,1,1,1,1);
    pg->addWidget(btnActivate,1,2,1,1);

    pg->setColumnStretch(1, 1);

    setLayout(pg);

    connect(btnCopy, &QPushButton::clicked, [=]() {
        QClipboard *board = QApplication::clipboard();
        board->setText(deviceId->text());
//        QString code = caculateChecksum(deviceId->text());
//        qDebug("code: %s", code.toStdString().c_str());
        //        codeEdit->setText(code);
        QMessageBox::information(this, "", "复制成功");
    });

    connect(btnActivate, &QPushButton::clicked, [=]() {
//        printf("code: %s", activateCode->text().toStdString().c_str());
        Configure::getInstance()->setActivateCode(activateCode->text());
        if(!Configure::getInstance()->isLicensed()) {
            QMessageBox::warning(this, "提示", "激活失败");
        } else {
            QMessageBox::warning(this, "提示", "激活成功");
            activateCode->setReadOnly(true);
        }
    });
}
