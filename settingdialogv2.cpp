#include "settingdialogv2.h"
#include <QGridLayout>
#include <QSpacerItem>
#include <QInputDialog>
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QDesktopServices>
#include "Configure.h"
#include "common.h"
#include "activatewidget.h"

SettingDialogV2::SettingDialogV2(QWidget *parent) : QDialog(parent)
{
    //    buttonBox = new QDialogButtonBox(this);
    //    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    //    buttonBox->setGeometry(QRect(190, 240, 341, 32));
    //    buttonBox->setOrientation(Qt::Horizontal);
    //    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    labelPicPath = new QLabel(this);
    labelPicPath->setText(tr("图片目录:"));

    editPicPath = new QLineEdit(this);

    btnPicPath = new QPushButton(this);
    btnPicPath->setText(tr("打开"));

    labelVideoPath = new QLabel(this);
    labelVideoPath->setText(tr("视频目录:"));

    editVideoPath = new QLineEdit(this);

    btnVideoPath = new QPushButton(this);
    btnVideoPath->setText(tr("打开"));


    labelCh1 = new QLabel(this);
    labelCh1->setText(tr("CH1 IP:"));

    labelCh2 = new QLabel(this);
    labelCh2->setText(tr("CH2 IP:"));

    labelCh3 = new QLabel(this);
    labelCh3->setText(tr("CH3 IP:"));


    editCh1 = new QLineEdit(this);
    editCh2 = new QLineEdit(this);
    editCh3 = new QLineEdit(this);

    btnCh1 = new QPushButton(this);
    btnCh1->setText(tr("保存"));

    btnCh2 = new QPushButton(this);
    btnCh2->setText(tr("保存"));

    btnCh3 = new QPushButton(this);
    btnCh3->setText(tr("保存"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok);


    QGridLayout *pg=new QGridLayout;
    //    pg->setVerticalSpacing(22);   //设置各子部件之间的垂直间距，不会为该间距分配索引。
    pg->addWidget(labelPicPath,0,0,1,1);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。
    pg->addWidget(editPicPath,0,1,1,2);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。
    pg->addWidget(btnPicPath,0,3,1,1);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。

    pg->addWidget(labelVideoPath,1,0,1,1);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。
    pg->addWidget(editVideoPath,1,1,1,2);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。
    pg->addWidget(btnVideoPath,1,3,1,1);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。

    pg->addWidget(labelCh1,2,0,1,1);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。
    pg->addWidget(editCh1,2,1,1,1);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。
    pg->addWidget(btnCh1,2,2,1,1);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。


    pg->addWidget(labelCh2,3,0,1,1);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。
    pg->addWidget(editCh2,3,1,1,1);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。
    pg->addWidget(btnCh2,3,2,1,1);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。

    pg->addWidget(labelCh3,4,0,1,1);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。
    pg->addWidget(editCh3,4,1,1,1);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。
    pg->addWidget(btnCh3,4,2,1,1);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。

    pg->addWidget(buttonBox, 5, 4, 1, 1, Qt::AlignTop|Qt::AlignLeft);

    setLayout(pg);

    pg->setRowStretch(5, 1);
    pg->setColumnStretch(4, 1);
    pg->setColumnMinimumWidth(1, 140);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

    connect(btnPicPath, SIGNAL(clicked()), this, SLOT(onChangePicPath()));
    connect(btnVideoPath, SIGNAL(clicked()), this, SLOT(onChangeVideoPath()));

    connect(btnCh1, &QPushButton::clicked, [=](){
        onSaveIp(0);
    }
    );
    connect(btnCh2, &QPushButton::clicked, [=](){
        onSaveIp(1);
    }
    );
    connect(btnCh3, &QPushButton::clicked, [=](){
        onSaveIp(2);
    }
    );


    setWindowTitle(tr("设置"));


    picPath = Configure::getInstance()->getPicpath();
    videoPath = Configure::getInstance()->getVideopath();

    editPicPath->setText(picPath);
    editVideoPath->setText(videoPath);

    ip1 = Configure::getInstance()->getCameraIp(0);
    ip2 = Configure::getInstance()->getCameraIp(1);
    ip3 = Configure::getInstance()->getCameraIp(2);

    editCh1->setText(ip1);
    editCh2->setText(ip2);
    editCh3->setText(ip3);
}

SettingDialogV2::~SettingDialogV2() {
    delete buttonBox;
}

void SettingDialogV2::resizeEvent(QResizeEvent *event) {
    //    int ax = event->size().width() - ui->buttonBox->width() - 20;
    //    int ay = (event->size().height() - ui->buttonBox->height()) - 20;
    //    ui->buttonBox->move(ax, ay);
    //    ay = ay - ui->buttonBox->height() - 20;
}


void SettingDialogV2::onChangePicPath() {
    bool ok = QDesktopServices::openUrl(QUrl(picPath));
    //    bool bOk = false;
    //        string sRtsp = QInputDialog::getText(this, tr("Open RTSP"),
    //            tr("RTSP url:"), QLineEdit::Normal,
    //            "rtsp://127.0.0.1:8554/test.mkv", &bOk).toStdString();

    //    QString path = QFileDialog::getExistingDirectory(this);
    //    if(!path.isEmpty()) {
    //        ui->picPath->setText(path);
    //    }

    //    printf("picPath:%s", path.toStdString().c_str());

    //    getExistingDirectory(QWidget *parent = nullptr, const QString &caption = QString(), const QString &dir = QString(), QFileDialog::Options options = ShowDirsOnly)

    //    SettingDialog *dlg=new SettingDialog(this);

    //    int ret = dlg->exec();
    //    if(ret==QDialog::Accepted) {
    //        printf("!ret:%d", ret);
    //    } else {
    //        printf("ret:%d", ret);
    //    }
    //    delete dlg;
}
void SettingDialogV2::onChangeVideoPath() {
    //    QString path = QFileDialog::getExistingDirectory(this);
    //    if(!path.isEmpty()) {
    //        ui->videoPath->setText(path);
    //    }

    //    printf("videoPath:%s", path.toStdString().c_str());

    bool ok = QDesktopServices::openUrl(QUrl(videoPath));
    printf("result: %d - %d", ok == true ? 1: 0, ok);
}

void SettingDialogV2::onSaveIp(int index) {
    printf("index: %d", index);
    switch (index) {
    case 0:
        Configure::getInstance()->setCameraIp(0, editCh1->text());
        break;
    case 1:
        Configure::getInstance()->setCameraIp(1, editCh2->text());
        break;
    case 2:
        Configure::getInstance()->setCameraIp(2, editCh3->text());
        break;
    }

}
