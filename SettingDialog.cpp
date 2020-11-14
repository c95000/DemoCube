#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include <QPushButton>
#include <QResizeEvent>
#include <QFileDialog>
#include <QWidget>
#include "common.h"
#include <string>
#include <QThread>
#include <time.h>
#include <QInputDialog>
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QDesktopServices>
#include "Configure.h"

using namespace std;


SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("确定");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->hide();
    connect(this, &QDialog::accept, this, &SettingDialog::accept);
    connect(ui->buttonPicPath, SIGNAL(clicked()), this, SLOT(onChangePicPath()));
    connect(ui->buttonVideoPath, SIGNAL(clicked()), this, SLOT(onChangeVideoPath()));

    setWindowTitle(tr("设置"));

//QDir::currentPath()
//QDir::homePath();
//    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
//    QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);

    picPath = Configure::getInstance()->getPicpath();
    videoPath = Configure::getInstance()->getVideopath();

    ui->picPath->setText(picPath);
    ui->videoPath->setText(videoPath);

//    ui->buttonPicPath->hide();
//    ui->buttonVideoPath->hide();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::resizeEvent(QResizeEvent *event) {
    int ax = event->size().width() - ui->buttonBox->width() - 20;
    int ay = (event->size().height() - ui->buttonBox->height()) - 20;
    ui->buttonBox->move(ax, ay);

//    ax = (event->size().width() - ui->company->width())/2;
    ay = ay - ui->buttonBox->height() - 20;
//    ui->company->move(ax, ay);
}

void SettingDialog::accept()
{
    printf("accetp");
    QDialog::accept();
}

void SettingDialog::onChangePicPath() {
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
void SettingDialog::onChangeVideoPath() {
//    QString path = QFileDialog::getExistingDirectory(this);
//    if(!path.isEmpty()) {
//        ui->videoPath->setText(path);
//    }

//    printf("videoPath:%s", path.toStdString().c_str());

    Configure::getInstance()->setValue();

    Configure::getInstance()->getValue();
    bool ok = QDesktopServices::openUrl(QUrl(videoPath));
    printf("result: %d - %d", ok == true ? 1: 0, ok);
}
