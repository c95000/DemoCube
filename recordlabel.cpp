#include "recordlabel.h"
#include "ui_recordlabel.h"
#include "Resolution.h"
#include <QHBoxLayout>
#include "common.h"

RecordLabel::RecordLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordLabel)
{
    ui->setupUi(this);
    int scaleX = Resolution::getInstance()->scaleX();
    int scaleY = Resolution::getInstance()->scaleY();
    QPixmap myPix(":/images/res/images/redpen.png");
    myPix = myPix.scaled(15 * scaleX, 15 * scaleY, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->recordIcon->setPixmap(myPix);
    ui->stopRecord->setImages(QPixmap(":/images/res/images/close.png"), scaleX * 50, scaleY * 50);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(ui->stopRecord, 0, Qt::AlignHCenter);
    layout->addWidget(ui->recordTime, 0, Qt::AlignHCenter);
    layout->addWidget(ui->recordIcon, 0, Qt::AlignHCenter);
    layout->addStretch(1);
    setLayout(layout);

    QFont font = ui->recordTime->font();
    font.setPixelSize(scaleX * 28);
    ui->recordTime->setFont(font);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(255, 255, 255, 32)); //设置背景黑色
    setAutoFillBackground(true);
    setPalette(pal);

    connect(ui->stopRecord, &QPushButton::clicked, this, &RecordLabel::onStopRecord);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeUpdate()));

    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    setFixedSize(scaleX * 250, scaleY * 85);
    //      startRecord();
}

RecordLabel::~RecordLabel()
{
    delete ui;
}

void RecordLabel::onStopRecord(){
    timer->stop();
    emit stopRecord();
}

void RecordLabel::onTimeUpdate(){
    QDateTime current = QDateTime::currentDateTime();
    qint64 diff = startTime.msecsTo(current);
    QTime time = QTime::fromMSecsSinceStartOfDay(diff);
    ui->recordTime->setText(time.toString("hh:mm:ss"));
//    QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz")

    if(ui->recordIcon->isHidden()) {
        ui->recordIcon->show();
    } else {
        ui->recordIcon->hide();
    }
}

void RecordLabel::startRecord(){
    QTime time = QTime::fromMSecsSinceStartOfDay(0);
    ui->recordTime->setText(time.toString("hh:mm:ss"));
    startTime = QDateTime::currentDateTime();
    timer->start(500);
}
