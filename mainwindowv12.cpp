#include "mainwindowv12.h"
#include "ui_mainwindowv12.h"
#include <QPushButton>
#include <QHBoxLayout>
#include "glvideowidget.h"
#include "common.h"
#include "Configure.h"
#include "Loading/Loading.h"
#include <QTimer>
#include <QLabel>
#include <QDateTime>
#include "ffplayer.h"
#include "SettingDialog.h"
#include "aboutdialog.h"
#include "deviceinfo.h"
#include "Configure.h"

MainWindowV12::MainWindowV12(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowV12)
{
    ui->setupUi(this);
    setWindowTitle("实训优学 v2.0");

    int bottomMinimumHeight = 120;
    int default_width = 1280 * Resolution::getInstance()->scaleX();
    int default_height = 720 * Resolution::getInstance()->scaleY();
    resize(QSize(default_width, default_height));

    videoView = new VlcPlayer();//new QLabel("videoView");
    cameraView = new FFPlayer();//new QLabel("cameraView");
    whiteboardView = new FreeDrawing();//new QLabel("whiteboardView");


    viewStack = new QStackedWidget();
    viewStack->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    viewStack->setStyleSheet("QStackedWidget{background-color:#aaaaaa;}");
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
    controllerStack->setStyleSheet("QStackedWidget{}");

    controllerStack->addWidget(videoController);
    controllerStack->addWidget(cameraController);
    controllerStack->addWidget(whiteboardController);
    controllerStack->addWidget(new QWidget());
    controllerStack->setCurrentIndex(controllerStack->count() - 1);

    navigator = new Navigator();
    QStackedWidget* navigatorStack = new QStackedWidget();
    navigatorStack->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    navigatorStack->setMinimumHeight(bottomMinimumHeight);
    navigatorStack->setStyleSheet("QStackedWidget{}");
    navigatorStack->addWidget(navigator);

    assist = new Assist();

    // bottom
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(navigatorStack);
//    bottomLayout->addStretch();
    bottomLayout->addWidget(controllerStack, 1);
//    bottomLayout->addStretch();
    bottomLayout->addWidget(assist);


    // whole
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(viewStack, 1);
    vLayout->addLayout(bottomLayout);




    QPushButton *pb,*pb1,*pb2,*pb3,*pb4,*pb5,*pb6;
    pb=new QPushButton("AAA");   	 pb1=new QPushButton("BBB");    pb2=new QPushButton("CCC");
    pb3=new QPushButton("DDD");    pb4=new QPushButton("EEE");
    pb5=new QPushButton("FFF");    pb6=new QPushButton("GGG");

    QWidget *pw1;
    pw1 = new QWidget();
    pw1->setStyleSheet("background-color:black;");

    QGridLayout *pg=new QGridLayout;
//    pg->setVerticalSpacing(22);   //设置各子部件之间的垂直间距，不会为该间距分配索引。
    pg->addWidget(viewStack,0,0,1,2);  //把按钮pb添加到第0行0列，该按钮占据1行和1列单元格。
//    pg->addWidget(pb1,0,1,1,1);
    pg->addWidget(navigatorStack,1,0,1,1);  //该按钮占据3列单元格的宽度
    pg->addWidget(controllerStack,1,1,1,1);  //该按钮占据3列单元格的宽度
    pg->addWidget(assist,1,2,1,1);  //pb3在其单元格内左下对齐
    ui->centralwidget->setLayout(pg);

    pg->setRowStretch(0, 1);
    pg->setRowStretch(1, 0);
    pg->setColumnStretch(1, 1);
//    pg->setColumnStretch(0, 1);
//    pg->setColumnStretch(1, 0);
//    pg->setRowMinimumHeight(1,100);  //把第2行的最小高度设置为66像素
//    pg->setColumnMinimumWidth(1,100);  //把第0列的最小宽度设置为111像素

    printf("column: %d row: %d", pg->columnCount(), pg->rowCount());

//    ui->centralwidget->setLayout(vLayout);


    arnetWrapper = new ArnetWrapper();

    connect(navigator, SIGNAL(buttonToggled(int, bool)), this, SLOT(onButtonToggled(int, bool)));

//    freeDrawing = new FreeDrawing();
//    vlcPlayer = new VlcPlayer();
//    vLayout->addStretch(0);
//    vLayout->addLayout(hLayout);
//    ui->centralwidget->setLayout(vLayout);

    connectViewSignals();
    connectCameraSignals();
    connectWhiteboardSignals();

    loading = new Loading(this);
    loading->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    loading->setWindowModality(Qt::ApplicationModal);
    loading->resize(256, 256);
    loading->setMaxDiameter(20);
    loading->setMinDiameter(1);
    loading->start();

    navigator->setChecked(1);
}

MainWindowV12::~MainWindowV12()
{
    delete ui;
}


void MainWindowV12::connectViewSignals() {
    connect(videoController, SIGNAL(play(const QString&)), videoView, SLOT(play(const QString&)));

    connect(videoController, SIGNAL(play()), videoView, SLOT(play()));
    connect(videoController, SIGNAL(pause()), videoView, SLOT(pause()));
    connect(videoController, SIGNAL(stop()), videoView, SLOT(stop()));
    connect(videoController, SIGNAL(takePicture()), videoView, SLOT(takePicture()));
    connect(videoController, SIGNAL(comment()), this, SLOT(on_btnComment()));

    connect(videoView, SIGNAL(played()), videoController, SLOT(played()));
    connect(videoView, SIGNAL(paused()), videoController, SLOT(paused()));
    connect(videoView, SIGNAL(stopped()), videoController, SLOT(stopped()));

    connect(videoView, SIGNAL(updateProgress(int, int)), videoController, SLOT(updateProgress(int, int)));
}
void MainWindowV12::connectCameraSignals() {

    connect(cameraController, SIGNAL(signalDisconnect()), cameraView, SLOT(stop()));
    connect(cameraController, SIGNAL(play()), cameraView, SLOT(play()));
    connect(cameraController, SIGNAL(pause()), cameraView, SLOT(pause()));
    connect(cameraController, SIGNAL(takePicture()), cameraView, SLOT(takePicture()));
    connect(cameraController, SIGNAL(comment()), this, SLOT(on_btnComment()));

    connect(cameraView, SIGNAL(played()), cameraController, SLOT(played()));
    connect(cameraView, SIGNAL(paused()), cameraController, SLOT(paused()));
    connect(cameraView, SIGNAL(stopped()), cameraController, SLOT(stopped()));


    connect(cameraController, SIGNAL(startRecord()), cameraView, SLOT(startRecord()));
    connect(cameraController, SIGNAL(stopRecord()), cameraView, SLOT(stopRecord()));
    connect(cameraView, SIGNAL(startRecorded()), cameraController, SLOT(startRecorded()));
    connect(cameraView, SIGNAL(stopRecorded()), cameraController, SLOT(stopRecorded()));

    connect(cameraController, SIGNAL(zoomTele()), arnetWrapper, SLOT(zoomTele()));
    connect(cameraController, SIGNAL(zoomWide()), arnetWrapper, SLOT(zoomWide()));
    connect(cameraController, SIGNAL(zoomStop()), arnetWrapper, SLOT(zoomStop()));
    connect(cameraController, SIGNAL(rotation()), cameraView, SLOT(rotation()));
    connect(arnetWrapper, SIGNAL(error(int)), this, SLOT(onError(int)));

    connect(cameraController, SIGNAL(signalConnect(const QString&)), this, SLOT(onConnect(const QString&)));
    connect(cameraController, SIGNAL(signalConnect(const int)), this, SLOT(onConnect(const int)));
}
void MainWindowV12::connectWhiteboardSignals() {

    connect(whiteboardController, SIGNAL(signalColorChanged(int)), whiteboardView, SLOT(on_colorChanged(int)));
    connect(whiteboardController, SIGNAL(signalWidthChanged(int)), whiteboardView, SLOT(on_widthChanged(int)));
    connect(whiteboardController, SIGNAL(signalUndo()), whiteboardView, SLOT(on_btnUndo()));
    connect(whiteboardController, SIGNAL(signalClear()), whiteboardView, SLOT(on_btnClear()));
    connect(whiteboardController, SIGNAL(signalClose()), whiteboardView, SLOT(on_btnClose()));
    connect(whiteboardController, SIGNAL(onPenChanged(int, int)), whiteboardView, SLOT(on_penChanged(int, int)));
}

void MainWindowV12::checkPermission(){
    QString biosSn = getBiosSerialnumber();
    QString bbSn = getBaseboardSerialnumber();
    QString bbUuid = getBaseboardUuid();
    QString content = tr("%1-%2-%3").arg(biosSn).arg(bbSn).arg(bbUuid).toStdString().c_str();
    printf(content.toStdString().c_str());

    QString md5;
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba.append(content);
    md.addData(content.toUtf8());
    bb = md.result();
    md5.append(bb.toHex());
    printf("md5 value: %s", md5.toStdString().c_str());
}

void MainWindowV12::onConnect(const QString ip) {

    loading->show();
//    bool ret = arnetWrapper->connect(ip);
    bool ret = true;
    if(ret) {
        loading->close();
        FFPlayer *ffplayer = static_cast<FFPlayer*>(cameraView);
        ffplayer->play(ip);
    } else {
        loading->close();
        onError(-101);
    }
}

void MainWindowV12::onConnect(const int index) {

    QString ip = Configure::getInstance()->getCameraIp(index);

    if(ip.isNull() || ip.isEmpty()) {
        bool isOK;//QInputDialog 是否成功得到输入
        ip = QInputDialog::getText(NULL,
                                   "设置",
                                   "输入摄像头IP，如: 192.168.1.100",
                                   QLineEdit::Normal,
                                   ip,
                                   &isOK);
    }

    Configure::getInstance()->setCameraIp(index, ip);
    printf("text: %s", ip.toStdString().c_str());

    loading->show();
    bool ret = arnetWrapper->connect(ip);
    if(ret) {
        loading->close();
        FFPlayer *ffplayer = static_cast<FFPlayer*>(cameraView);
        ffplayer->play(ip);
    } else {
        loading->close();
        onError(-101);
        ((CameraController1*)cameraController)->connectFailed(index);
    }
}

void MainWindowV12::replaceWidget(QWidget* widget) {
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

void MainWindowV12::on_btnLocal_clicked() {
    printf("on_btnLocal_clicked");
    QString videoPath = Configure::getInstance()->getVideopath();
    QString filename=QFileDialog::getOpenFileName(this,tr("action"),videoPath,"",0);
    if(filename.isEmpty()) {
        return;
    }

    printf("filename: %s", filename.toStdString().c_str());
    filename.replace("/", "\\");
    replaceWidget(vlcPlayer);
    vlcPlayer->play(filename);
}

void MainWindowV12::on_btnRtsp_clicked() {
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

void MainWindowV12::on_btnWhiteboard_clicked() {
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

    replaceWidget(freeDrawing);
}

void MainWindowV12::on_btnComment() {
    printf("MainWindowV12 %s() widget:%p", __FUNCTION__, viewStack->currentWidget());
    VlcPlayer *vlcPlayer = dynamic_cast<VlcPlayer*>(viewStack->currentWidget());
    printf("vlcPlayer: %p", vlcPlayer);
    if(nullptr != vlcPlayer) {
        QPixmap pixmap = vlcPlayer->snapshot();
        FreeDrawing *freeDrawing = dynamic_cast<FreeDrawing*>(whiteboardView);
        freeDrawing->clear(pixmap);
        navigator->setChecked(2);
        return;
    }

    FFPlayer *ffPlayer = dynamic_cast<FFPlayer*>(viewStack->currentWidget());
    if(nullptr != ffPlayer) {
        QPixmap pixmap = ffPlayer->snapshot();
        FreeDrawing *freeDrawing = dynamic_cast<FreeDrawing*>(whiteboardView);
        freeDrawing->clear(pixmap);
        navigator->setChecked(2);
        return;
    }
//    VlcPlayerController *vlcPlayerController = dynamic_cast<VlcPlayerController*>(viewStack->currentWidget());
//    printf("vlcPlayerController: %p", vlcPlayerController);


}

void MainWindowV12::on_btnTest1_clicked() {
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


void MainWindowV12::on_btnTest2_clicked() {
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

void MainWindowV12::onButtonToggled(int index, bool checked) {
//    printf("%s(%d, %d)", __FUNCTION__, index, checked);
//    printf("%s viewStack count:%d cuurentIndex:%d)", __FUNCTION__, viewStack->count(), viewStack->currentIndex());
//    printf("%s controllerStack count:%d cuurentIndex:%d)", __FUNCTION__, controllerStack->count(), controllerStack->currentIndex());
    if(checked) {
        viewStack->setCurrentIndex(index);
        controllerStack->setCurrentIndex(index);
    }
}

void MainWindowV12::onDirSetting() {
    printf("onSettingButtonClicked");
    SettingDialog *dlg=new SettingDialog(this);

    int ret = dlg->exec();
    if(ret==QDialog::Accepted) {
        printf("!ret:%d", ret);
    } else {
        printf("ret:%d", ret);
    }
    delete dlg;
}

void MainWindowV12::onActAbout() {
//    printf("onSettingButtonClicked");
//    SettingDialog *dlg=new SettingDialog(this);

//    int ret = dlg->exec();
//    if(ret==QDialog::Accepted) {
//        printf("!ret:%d", ret);
//    } else {
//        printf("ret:%d", ret);
//    }
//    delete dlg;

    printf("onSettingButtonClicked");
    AboutDialog *dlg=new AboutDialog(this);

    int ret = dlg->exec();
    if(ret==QDialog::Accepted) {
        printf("!ret:%d", ret);
    } else {
        printf("ret:%d", ret);
    }
    delete dlg;
}

void MainWindowV12::on_btnConnect() {
    printf("%s", __FUNCTION__);
}

void MainWindowV12::onError(int errorCode) {
    printf("errorcode : %d", errorCode);
//    QMessageBox::critical(this, "错误", tr("error(%1)").arg(errorCode));
    QMessageBox::critical(this, "错误", tr("连接失败").arg(errorCode));
}

void MainWindowV12::resizeEvent(QResizeEvent *event) {
//    QSize viewStackSize = viewStack->size();
//    printf("viewStackSize %d x %d", viewStackSize.width(), viewStackSize.height());
//    QSizeF destSz = QSizeF(16, 9).scaled(viewStackSize, Qt::KeepAspectRatio);
//    viewStack->resize(QSize(round(destSz.width()), round(destSz.height())));
}
