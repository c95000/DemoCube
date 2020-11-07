#include "primewindow.h"
#include "ui_primewindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include "glvideowidget.h"
#include "common.h"
#include "Configure.h"
#include "Loading/Loading.h"
#include <QTimer>
#include <QLabel>
#include <QDateTime>

PrimeWindow::PrimeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PrimeWindow)
{
    ui->setupUi(this);

//    setFixedSize(320, 240);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setAlignment(Qt::AlignTop);
    QPushButton *btnLocal = new QPushButton("本地文件");
    QPushButton *btnCamera = new QPushButton("摄像头");
    QPushButton *btnWhiteboard = new QPushButton("白板");
    QPushButton *btnTest1 = new QPushButton("test1");
    QPushButton *btnTest2 = new QPushButton("test2");
    connect(btnLocal, &QPushButton::clicked, this, &PrimeWindow::on_btnLocal_clicked);
    connect(btnCamera, &QPushButton::clicked, this, &PrimeWindow::on_btnRtsp_clicked);
    connect(btnWhiteboard, &QPushButton::clicked, this, &PrimeWindow::on_btnWhiteboard_clicked);
    connect(btnTest1, &QPushButton::clicked, this, &PrimeWindow::on_btnTest1_clicked);
    connect(btnTest2, &QPushButton::clicked, this, &PrimeWindow::on_btnTest2_clicked);

    hLayout->addWidget(btnLocal);
    hLayout->addWidget(btnCamera);
    hLayout->addWidget(btnWhiteboard);
    hLayout->addWidget(btnTest1);
    hLayout->addWidget(btnTest2);
    hLayout->addStretch();

    QVBoxLayout *vLayout = new QVBoxLayout();

//    GLVideoWidget *viewWidget = new GLVideoWidget();
//    QLabel *label = new QLabel("test");
//    MyPaint *paint = new MyPaint();
    freeDrawing = new FreeDrawing();
    vlcPlayer = new VlcPlayer();
    vLayout->addStretch(0);
//    vLayout->addWidget(freeDrawing, 1);
    vLayout->addLayout(hLayout);
    ui->centralwidget->setLayout(vLayout);
}

PrimeWindow::~PrimeWindow()
{
    delete ui;
}

void PrimeWindow::replaseWidget(QWidget* widget) {
    QHBoxLayout *layout = static_cast<QHBoxLayout*>(ui->centralwidget->layout());
    for(int i = 0; i < layout->count(); i++) {
//        printf("layout->itemAt(%d): %p", i, layout->itemAt(i));
//        printf("layout->itemAt(%d)->widget(): %p - %p", i, layout->itemAt(i)->widget(), layout->itemAt(i)->layout());
        QLayoutItem* child = layout->itemAt(i);
        if(NULL != child && NULL != child->widget()) {
            printf("widget: %p  child->widget():%p", widget, child->widget());
            layout->takeAt(i);
            layout->removeWidget(child->widget());
            child->widget()->setParent(0);
//            delete child->widget();
            break;
        }
    }
    layout->insertWidget(1, widget, 1);
}

void PrimeWindow::on_btnLocal_clicked() {
    printf("on_btnLocal_clicked");
    QString videoPath = Configure::getInstance()->getVideopath();
    QString filename=QFileDialog::getOpenFileName(this,tr("action"),videoPath,"",0);
    if(filename.isEmpty()) {
        return;
    }

    printf("filename: %s", filename.toStdString().c_str());
    filename.replace("/", "\\");
    replaseWidget(vlcPlayer);
    vlcPlayer->play(filename);
}

void PrimeWindow::on_btnRtsp_clicked() {
    printf("on_btnRtsp_clicked");
    Loading *loading = new Loading(this);
    loading->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    loading->setWindowModality(Qt::ApplicationModal);
    loading->resize(128, 128);
    loading->setMaxDiameter(15);
    loading->setMinDiameter(0);
    loading->start();
    loading->show();


    QTimer *myTimer = new QTimer(this);
    myTimer->start(1000*10);
    connect(myTimer,&QTimer::timeout,[=](){

            myTimer->stop();
            static int i = 0;
            i++;
            //ui->lcdNumber->display(i);
            loading->close();
        });
}

void PrimeWindow::on_btnWhiteboard_clicked() {
//    printf("on_btnWhiteboard_clicked----------------------------------------");
//    QHBoxLayout *layout = static_cast<QHBoxLayout*>(ui->centralwidget->layout());
//    for(int i = 0; i < layout->count(); i++) {
////        printf("layout->itemAt(%d): %p", i, layout->itemAt(i));
////        printf("layout->itemAt(%d)->widget(): %p - %p", i, layout->itemAt(i)->widget(), layout->itemAt(i)->layout());
//        QLayoutItem* child = layout->itemAt(i);
//        if(NULL != child && NULL != child->widget()) {
//            layout->takeAt(i);
//            layout->removeWidget(child->widget());
//            child->widget()->setParent(0);
//            delete child->widget();
//            break;
//        }

//    }
////    FreeDrawing *freeDrawing = new FreeDrawing(tr("D:/test.png"));
//    FreeDrawing *freeDrawing = new FreeDrawing();
//    layout->insertWidget(1, freeDrawing, 1);

    replaseWidget(freeDrawing);
}

void PrimeWindow::on_btnTest1_clicked() {
    printf("on_btnTest1_clicked");
    QHBoxLayout *layout = static_cast<QHBoxLayout*>(ui->centralwidget->layout());
    printf("layout: %p", layout);
    printf("layout count:%d", layout->count());
    for(int i = 0; i < layout->count(); i++) {
        printf("layout->itemAt(%d): %p", i, layout->itemAt(i));
        printf("layout->itemAt(%d)->widget(): %p - %p", i, layout->itemAt(i)->widget(), layout->itemAt(i)->layout());
    }
//    QLabel * label = new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz"));
//    printf("new label: %p", label);
//    layout->insertWidget(1, label, 1);

    FreeDrawing *freeDrawing = new FreeDrawing(tr("D:/test.png"));
    layout->insertWidget(1, freeDrawing, 1);
}


void PrimeWindow::on_btnTest2_clicked() {
//    printf("on_btnTest2_clicked");

    QHBoxLayout *layout = static_cast<QHBoxLayout*>(ui->centralwidget->layout());
    printf("layout: %p", layout);
    printf("layout count:%d", layout->count());
    for(int i = 0; i < layout->count(); i++) {
        printf("layout->itemAt(%d): %p", i, layout->itemAt(i));
        printf("layout->itemAt(%d)->widget(): %p - %p", i, layout->itemAt(i)->widget(), layout->itemAt(i)->layout());
        QLayoutItem* child = layout->itemAt(i);
        if(NULL != child && NULL != child->widget()) {
            layout->takeAt(i);
            layout->removeWidget(child->widget());
            child->widget()->setParent(0);
            delete child->widget();
            break;
        }
    }

    FreeDrawing *freeDrawing = new FreeDrawing(tr("D:/test.png"));
    layout->insertWidget(1, freeDrawing, 1);

//    QLayoutItem* layoutItem = layout->takeAt(0);
//    delete layoutItem->widget();
}

