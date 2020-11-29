#include "activatedialog.h"
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QClipboard>
#include "deviceinfo.h"

ActivateDialog::ActivateDialog(QWidget *parent) : QDialog(parent)
{
    init();
}

void ActivateDialog::init() {
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("激活"));
//    setFixedSize(310, 240);

    QLabel *snLabel = new QLabel("软件序列号:");
    QLineEdit *snValue = new QLineEdit();
    snValue->setText(getDeviceInfo());
    snValue->setReadOnly(true);

    QPushButton *btnCopy = new QPushButton("复制");

    QLabel *codeLabel = new QLabel("激活码:");
    codeEdit = new QLineEdit();

    QDialogButtonBox *buttonBox = new QDialogButtonBox();
    buttonBox->addButton(new QPushButton("确定"), QDialogButtonBox::AcceptRole);
    buttonBox->addButton(new QPushButton("取消"), QDialogButtonBox::RejectRole);
    connect(buttonBox, &QDialogButtonBox::accepted, [=](){
        printf("accepted");
        emit accept();
    });

    connect(buttonBox, &QDialogButtonBox::rejected, [=](){
        printf("rejected");
        emit reject();
    });

    QVBoxLayout *vLayout = new QVBoxLayout();
//    vLayout->setAlignment(Qt::AlignHCenter);

    vLayout->addStretch();
    vLayout->addWidget(snLabel);
    vLayout->addWidget(snValue);
    vLayout->addWidget(btnCopy);
    vLayout->addSpacing(30);
    vLayout->addWidget(codeLabel);
    vLayout->addWidget(codeEdit);
    vLayout->addStretch();
    vLayout->addWidget(buttonBox);
    setLayout(vLayout);

    connect(btnCopy, &QPushButton::clicked, [=]() {
        QClipboard *board = QApplication::clipboard();
        board->setText(snValue->text());
//        QString code = caculateChecksum(snValue->text());
//        codeEdit->setText(code);
    });
}

QString ActivateDialog::getCode() const {
    return codeEdit->text();
}
