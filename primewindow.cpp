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
    setWindowTitle("实训优学 v1.0");

//    setFixedSize(320, 240);

//    QHBoxLayout *hLayout = new QHBoxLayout();
//    hLayout->setAlignment(Qt::AlignTop);
//    QPushButton *btnLocal = new QPushButton("本地文件");
//    QPushButton *btnCamera = new QPushButton("摄像头");
//    QPushButton *btnWhiteboard = new QPushButton("白板");
//    QPushButton *btnTest1 = new QPushButton("test1");
//    QPushButton *btnTest2 = new QPushButton("test2");
//    connect(btnLocal, &QPushButton::clicked, this, &PrimeWindow::on_btnLocal_clicked);
//    connect(btnCamera, &QPushButton::clicked, this, &PrimeWindow::on_btnRtsp_clicked);
//    connect(btnWhiteboard, &QPushButton::clicked, this, &PrimeWindow::on_btnWhiteboard_clicked);
//    connect(btnTest1, &QPushButton::clicked, this, &PrimeWindow::on_btnTest1_clicked);
//    connect(btnTest2, &QPushButton::clicked, this, &PrimeWindow::on_btnTest2_clicked);

//    hLayout->addWidget(btnLocal);
//    hLayout->addWidget(btnCamera);
//    hLayout->addWidget(btnWhiteboard);
//    hLayout->addWidget(btnTest1);
//    hLayout->addWidget(btnTest2);
//    hLayout->addStretch();

//    QPalette pal(palette());
//    pal.setColor(QPalette::Background, QColor(100,0,0)); //设置背景黑色
//    setAutoFillBackground(true);
//    setPalette(pal);

    int bottomMinimumHeight = 120;
    int default_width = 1280 * Resolution::getInstance()->scaleX();
    int default_height = 720 * Resolution::getInstance()->scaleY();
    resize(QSize(default_width, default_height));

    videoView = new VlcPlayer();//new QLabel("videoView");
    cameraView = new CameraView();//new QLabel("cameraView");
    whiteboardView = new FreeDrawing();//new QLabel("whiteboardView");


    viewStack = new QStackedWidget();
    viewStack->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    viewStack->setStyleSheet("QStackedWidget{border:1px solid #aaaaaa;}");
    viewStack->addWidget(videoView);
    viewStack->addWidget(cameraView);
    viewStack->addWidget(whiteboardView);
    QWidget* defaultWidget = new QWidget();
    viewStack->addWidget(defaultWidget);
    viewStack->setCurrentIndex(viewStack->count() - 1);


    videoController = new VlcPlayerController();//new QLabel("videoController");
    cameraController = new CameraController1();//new QLabel("cameraController");
    whiteboardController = new FreeDrawingMenu();


    controllerStack = new QStackedWidget();
    controllerStack->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    controllerStack->setMinimumHeight(bottomMinimumHeight);
    controllerStack->setStyleSheet("QStackedWidget{border-radius:10px;border:1px solid #aaaaaa;}");

    controllerStack->addWidget(videoController);
    controllerStack->addWidget(cameraController);
    controllerStack->addWidget(whiteboardController);
    controllerStack->addWidget(new QWidget());
    controllerStack->setCurrentIndex(controllerStack->count() - 1);

    navigator = new Navigator();
    QStackedWidget* navigatorStack = new QStackedWidget();
    navigatorStack->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    navigatorStack->setMinimumHeight(bottomMinimumHeight);
    navigatorStack->setStyleSheet("QStackedWidget{border-radius:10px;border:1px solid #aaaaaa;}");
    navigatorStack->addWidget(navigator);

    // bottom
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(navigatorStack);
//    bottomLayout->addStretch();
    bottomLayout->addWidget(controllerStack, 1);
//    bottomLayout->addStretch();


    // whole
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(viewStack, 1);
    vLayout->addLayout(bottomLayout);

    ui->centralwidget->setLayout(vLayout);



    connect(navigator, SIGNAL(buttonToggled(int, bool)), this, SLOT(onButtonToggled(int, bool)));

//    freeDrawing = new FreeDrawing();
//    vlcPlayer = new VlcPlayer();
//    vLayout->addStretch(0);
//    vLayout->addLayout(hLayout);
//    ui->centralwidget->setLayout(vLayout);

    connectViewSignals();
    connectCameraSignals();
    connectWhiteboardSignals();
}

PrimeWindow::~PrimeWindow()
{
    delete ui;
}

void PrimeWindow::paintEvent(QPaintEvent *event) {
//    if(!Configure::getInstance()->isOfficial()) {
//        QTextOption option(Qt::AlignLeft | Qt::AlignTop);
//        option.setWrapMode(QTextOption::WordWrap);
//        QRectF rect(100, 100, this->width(), this->height());
//        QString date = QDateTime::currentDateTime().toString("欢迎使用软件, 现在时刻：yyyy-MM-dd hh:mm:ss.zzz");

//        // Render text
//        QPainter painter(this);

//        QFont font;
//        font.setPixelSize(40);
//        painter.setFont(font);

//        QPen pen;
//        pen.setColor(Qt::red);
//        painter.setPen(pen);

//        painter.drawText(rect, date, option);
//        painter.end();
//    }
}

void PrimeWindow::connectViewSignals() {
    connect(videoController, SIGNAL(play(const QString&)), videoView, SLOT(play(const QString&)));

    connect(videoController, SIGNAL(play()), videoView, SLOT(play()));
    connect(videoController, SIGNAL(pause()), videoView, SLOT(pause()));
    connect(videoController, SIGNAL(stop()), videoView, SLOT(stop()));
    connect(videoController, SIGNAL(takePicture()), videoView, SLOT(takePicture()));
    connect(videoController, SIGNAL(comment()), this, SLOT(on_btnComment()));

    connect(videoView, SIGNAL(played()), videoController, SLOT(played()));
    connect(videoView, SIGNAL(paused()), videoController, SLOT(paused()));
    connect(videoView, SIGNAL(stopped()), videoController, SLOT(stopped()));
}
void PrimeWindow::connectCameraSignals() {

//    void signalConnect(const QString& sourceUrl);
//    void signalDisconnect();
//    void play();
//    void pause();
//    void takePicture();
//    void comment();

    connect(cameraController, SIGNAL(signalConnect(const QString&)), cameraView, SLOT(onConnect(const QString&)));
    connect(cameraController, SIGNAL(signalDisconnect()), cameraView, SLOT(onDisconnect()));
    connect(cameraController, SIGNAL(play()), cameraView, SLOT(play()));
    connect(cameraController, SIGNAL(pause()), cameraView, SLOT(pause()));
    connect(cameraController, SIGNAL(stop()), cameraView, SLOT(stop()));
    connect(cameraController, SIGNAL(takePicture()), cameraView, SLOT(takePicture()));
    connect(cameraController, SIGNAL(comment()), this, SLOT(on_btnComment()));


    connect(cameraView, SIGNAL(played()), cameraController, SLOT(played()));
    connect(cameraView, SIGNAL(paused()), cameraController, SLOT(paused()));
    connect(cameraView, SIGNAL(stopped()), cameraController, SLOT(stopped()));
}
void PrimeWindow::connectWhiteboardSignals() {

    connect(whiteboardController, SIGNAL(signalColorChanged(int)), whiteboardView, SLOT(on_colorChanged(int)));
    connect(whiteboardController, SIGNAL(signalWidthChanged(int)), whiteboardView, SLOT(on_widthChanged(int)));
    connect(whiteboardController, SIGNAL(signalUndo()), whiteboardView, SLOT(on_btnUndo()));
    connect(whiteboardController, SIGNAL(signalClear()), whiteboardView, SLOT(on_btnClear()));
    connect(whiteboardController, SIGNAL(signalClose()), whiteboardView, SLOT(on_btnClose()));
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

void PrimeWindow::on_btnComment() {
    printf("PrimeWindow %s() widget:%p", __FUNCTION__, viewStack->currentWidget());
    VlcPlayer *vlcPlayer = dynamic_cast<VlcPlayer*>(viewStack->currentWidget());
    printf("vlcPlayer: %p", vlcPlayer);
    if(nullptr != vlcPlayer) {
        QPixmap pixmap = vlcPlayer->snapshot();
        FreeDrawing *freeDrawing = dynamic_cast<FreeDrawing*>(whiteboardView);
        freeDrawing->clear(pixmap);
        navigator->setChecked(2);
        return;
    }

    CameraView *cameraView = dynamic_cast<CameraView*>(viewStack->currentWidget());
    if(nullptr != cameraView) {
        QPixmap pixmap = cameraView->snapshot();
        FreeDrawing *freeDrawing = dynamic_cast<FreeDrawing*>(whiteboardView);
        freeDrawing->clear(pixmap);
        navigator->setChecked(2);
        return;
    }
//    VlcPlayerController *vlcPlayerController = dynamic_cast<VlcPlayerController*>(viewStack->currentWidget());
//    printf("vlcPlayerController: %p", vlcPlayerController);


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
//    QHBoxLayout *layout = static_cast<QHBoxLayout*>(ui->centralwidget->layout());
//    printf("layout: %p", layout);
//    printf("layout count:%d", layout->count());
//    for(int i = 0; i < layout->count(); i++) {
//        printf("layout->itemAt(%d): %p", i, layout->itemAt(i));
//        printf("layout->itemAt(%d)->widget(): %p - %p", i, layout->itemAt(i)->widget(), layout->itemAt(i)->layout());
//        QLayoutItem* child = layout->itemAt(i);
//        if(NULL != child && NULL != child->widget()) {
//            layout->takeAt(i);
//            layout->removeWidget(child->widget());
//            child->widget()->setParent(0);
//            delete child->widget();
//            break;
//        }
//    }

//    FreeDrawing *freeDrawing = new FreeDrawing(tr("D:/test.png"));
//    layout->insertWidget(1, freeDrawing, 1);
}

void PrimeWindow::onButtonToggled(int index, bool checked) {
    printf("%s(%d, %d)", __FUNCTION__, index, checked);
    printf("%s viewStack count:%d cuurentIndex:%d)", __FUNCTION__, viewStack->count(), viewStack->currentIndex());
    printf("%s controllerStack count:%d cuurentIndex:%d)", __FUNCTION__, controllerStack->count(), controllerStack->currentIndex());
    if(checked) {
        viewStack->setCurrentIndex(index);
        controllerStack->setCurrentIndex(index);
    }
}

void PrimeWindow::on_btnConnect() {
    printf("%s", __FUNCTION__);
}

