#include "imagedisplay.h"
#include "ui_imagedisplay.h"
#include "common.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include "yuv2jpg.h"

ImageDisplay::ImageDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageDisplay)
{
    ui->setupUi(this);

    QPushButton *btnOpen = new QPushButton("open file");
    connect(btnOpen, SIGNAL(clicked(bool)), this, SLOT(onBtnOpen()));

    QPushButton *btnNext = new QPushButton("next frame");
    connect(btnNext, SIGNAL(clicked(bool)), this, SLOT(onBtnNext()));

    QPushButton *btnPlay = new QPushButton("play");
    connect(btnPlay, SIGNAL(clicked(bool)), this, SLOT(onBtnPlay()));

    IconButon *iconButton = new IconButon(QString(":/res/icons/account_circle_outline.svg"), QString(":/res/icons/account_circle.svg"));


    imageView = new QLabel();

    QPalette pal(imageView->palette());
    pal.setColor(QPalette::Background, QColor(228,228,228)); //设置背景黑色
    imageView->setAutoFillBackground(true);
    imageView->setPalette(pal);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(imageView, 1);
    vLayout->addWidget(btnOpen, 0, Qt::AlignCenter);
    vLayout->addWidget(btnNext, 0, Qt::AlignCenter);
    vLayout->addWidget(btnPlay, 0, Qt::AlignCenter);
    vLayout->addWidget(iconButton, 0, Qt::AlignCenter);
    setLayout(vLayout);

    m_vlcPlayer = NULL;

    //创建vlc实例
    m_vlcInstance = libvlc_new(0, NULL);

    //判断vlc实例化是否ok
    if (m_vlcInstance == NULL)
    {
        QMessageBox::critical(this, "Qt libVLC player", "Could not init libVLC");
        exit(1);
    }
}

ImageDisplay::~ImageDisplay()
{
    delete ui;
    delete imageView;
}

static int m_currentFrameIndex = 0;
int m_width = 864;
int m_height = 514;
QString m_fileName;

void ImageDisplay::onBtnOpen() {
    printf("onBtnOpen");
    printf("on_btnLocal_clicked");
    QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString filename=QFileDialog::getOpenFileName(this,tr("action"),path,"",0);
    if(filename.isEmpty()) {
        return;
    }

    printf("filename: %s", filename.toStdString().c_str());
    m_fileName = filename;

    QFile file(m_fileName);
    file.open(QIODevice::ReadOnly);

    printf("fileRead:%lld", file.size());

    QByteArray data = file.readAll();


    YUV2JPG yuv2jpg;

    yuv2jpg.archive(data.data(), 1280, 738, 16);
}

void ImageDisplay::onBtnNext() {
    quint16 n = 64;
    QByteArray data;
    QFile fileRead(m_fileName);
    fileRead.open(QIODevice::ReadOnly);

    printf("fileSize:%lld", fileRead.size());
    int frameSize = ((m_width * m_height) << 2) + 99;
    fileRead.seek(frameSize * m_currentFrameIndex);
    m_currentFrameIndex += 10;
    data = fileRead.read(frameSize);
    if(data.size() != frameSize) {
        return;
    }

    printf("datasize:%d m_currentFrameIndex:%d", data.size(), m_currentFrameIndex);
    QImage image((uchar*)data.data(), m_width, m_height, QImage::Format_ARGB32);
    QPixmap pixmap = QPixmap::fromImage(image);;
    imageView->setPixmap(pixmap);

}

void ImageDisplay::onBtnPlay() {
    printf("onBtnPlay");
    QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString filename=QFileDialog::getOpenFileName(this,tr("action"),path,"",0);
    if(filename.isEmpty()) {
        return;
    }


    std::string tempStr = filename.replace("/","\\").toStdString();
    printf("filename: %s", tempStr.c_str());


    libvlc_media_t *vlcMedia = libvlc_media_new_path(m_vlcInstance, tempStr.c_str());
    if (!vlcMedia)
    {
        printf("failed.");
        return;
    }

    m_vlcPlayer = libvlc_media_player_new_from_media(vlcMedia);
    libvlc_media_release(vlcMedia);

    //vlcplayer和Qt控件关联
    libvlc_media_player_set_hwnd(m_vlcPlayer, (void*)(imageView->winId()));
    libvlc_media_player_play(m_vlcPlayer);

    printf("play ok.");

}
