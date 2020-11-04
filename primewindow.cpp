#include "primewindow.h"
#include "ui_primewindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include "glvideowidget.h"
#include "common.h"
#include "Configure.h"

PrimeWindow::PrimeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PrimeWindow)
{
    ui->setupUi(this);

    setFixedSize(320, 240);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setAlignment(Qt::AlignBottom);
    QPushButton *btnLocal = new QPushButton("本地文件");
    QPushButton *btnCamera = new QPushButton("摄像头");
    QPushButton *btnWhiteboard = new QPushButton("白板");
    connect(btnLocal, &QPushButton::clicked, this, &PrimeWindow::on_btnLocal_clicked);
    connect(btnCamera, &QPushButton::clicked, this, &PrimeWindow::on_btnRtsp_clicked);
    connect(btnWhiteboard, &QPushButton::clicked, this, &PrimeWindow::on_btnWhiteboard_clicked);

    hLayout->addWidget(btnLocal);
    hLayout->addWidget(btnCamera);
    hLayout->addWidget(btnWhiteboard);
    hLayout->addStretch();

    QVBoxLayout *vLayout = new QVBoxLayout(this);

    GLVideoWidget *viewWidget = new GLVideoWidget(this);
    vLayout->addWidget(viewWidget, 1);
    vLayout->addLayout(hLayout);

    ui->centralwidget->setLayout(vLayout);
}

PrimeWindow::~PrimeWindow()
{
    delete ui;
}


void PrimeWindow::on_btnLocal_clicked() {
    printf("on_btnLocal_clicked");
    QString videoPath = Configure::getInstance()->getVideopath();
    QString filename=QFileDialog::getOpenFileName(this,tr("action"),videoPath,"",0);
    if(filename.isEmpty()) {
        return;
    }

    filename.replace("/", "\\");
}

void PrimeWindow::on_btnRtsp_clicked() {
    printf("on_btnRtsp_clicked");
}

void PrimeWindow::on_btnWhiteboard_clicked() {
    printf("on_btnWhiteboard_clicked");
}
