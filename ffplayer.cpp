#include "ffplayer.h"
#include "common.h"
#include "glvideowidget.h"


static void printError(int ret) {
    char msg[512];
    av_make_error_string(msg, 512, ret);
    printf("Error(%d)(%s).\n", ret, msg);
}

static void writeFile(const QString& filename, const char* data, int size) {
    QFile f(filename);
    f.open(QIODevice::WriteOnly | QIODevice::Append);
    f.write(data, size);
    f.close();
}

static QString picPath;
static QString fileName;

void _ffdecoder_video_format_cb(void *opaque, int* width, int *height, int* lineSize) {
    FFPlayer* ffPlayer = (FFPlayer*)opaque;
    printf("*video size: %d x %d lineSize: %d / %d / %d", *width, *height, lineSize[0], lineSize[1], lineSize[2]);
    ffPlayer->setVideoSize(*width, *height);
    ffPlayer->videoView->setYUV420pParameters(*width, *height, lineSize);
}

void _ffdecoder_data_available_cb(void *opaque, const QByteArray& ba) {
    FFPlayer* ffPlayer = (FFPlayer*)opaque;
//    printf("ba size: %d opaque:%p", ba.size(), ffPlayer);

//    if(fileName.isNull() || fileName.isEmpty()) {
//        picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
//        fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".yuv";
//    }
//    writeFile(fileName, (char *)ba.data(), ba.size());
    ffPlayer->videoView->setFrameData(ba);
}

FFPlayer::FFPlayer(QWidget *parent) : QWidget(parent)
{
    init();
}

FFPlayer::FFPlayer(const QString& inputSrc, QWidget *parent): inputSource(inputSrc) {
    init();
}

FFPlayer::~FFPlayer() {
    delete ffDecoder;
}

void FFPlayer::init() {
    videoView = new GLVideoWidget(this);
//    QVBoxLayout *layout = new QVBoxLayout();
//    layout->setContentsMargins(0, 0, 0, 0);
//    layout->addWidget(videoView);

//    setLayout(layout);

    ffDecoder = new FFDecoder();
    connect(ffDecoder, SIGNAL(prepared()), this, SIGNAL(prepared()));
    connect(ffDecoder, SIGNAL(played()), this, SIGNAL(played()));
    connect(ffDecoder, SIGNAL(stopped()), this, SIGNAL(stopped()));
    connect(ffDecoder, SIGNAL(paused()), this, SIGNAL(paused()));

    if(!inputSource.isNull() && !inputSource.isEmpty()) {
        play();
    }
}

void FFPlayer::play(const QString& inputSrc) {
//    inputSource = inputSrc;
    inputSource = tr("rtsp://%1/").arg(inputSrc);
    printf("inputSource is %s", inputSource.toStdString().c_str());
    ffDecoder->setSource(inputSource, _ffdecoder_video_format_cb, _ffdecoder_data_available_cb, this);
    ffDecoder->play();
}

void FFPlayer::play() {
    ffDecoder->play();
}

void FFPlayer::stop() {
    ffDecoder->stop();
}
void FFPlayer::pause() {
    ffDecoder->pause();
}
void FFPlayer::close() {

}
void FFPlayer::takePicture() {
    printf("VlcPlayer::%s():%p", __FUNCTION__, QThread::currentThreadId());
    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".png";
    printf("filename: %s", fileName.toStdString().c_str());
    if (fileName.length() > 0)
    {
        snapshot().save(fileName);
    }
}
void FFPlayer::comment() {

}

void FFPlayer::startRecord() {
    ffDecoder->startRecord();
    emit startRecorded();
}
void FFPlayer::stopRecord() {
    ffDecoder->stopRecord();
    emit stopRecorded();
}

const QPixmap FFPlayer::snapshot() {
//    QScreen *screen = QGuiApplication::primaryScreen();
//    QPixmap pixmap = screen->grabWindow(videoView->winId());
//    return pixmap;
    QImage img = videoView->grabFramebuffer();
    return QPixmap::fromImage(img);
}

void FFPlayer::setVideoSize(int width, int height) {
    this->videoWidth = width;
    this->videoHeight = height;
}

void FFPlayer::resizeEvent(QResizeEvent *event) {
    printf("FFPlayer resizeEvent: %d x %d", event->size().width(), event->size().height());
    QSizeF parentSize = parentWidget()->size();
    QSizeF destSz = QSizeF(16, 9).scaled(parentSize, Qt::KeepAspectRatio);
    videoView->resize(QSize(round(destSz.width()), round(destSz.height())));

    QSize psz = size();
    QPoint center((psz.width() - destSz.width())/2, (psz.height() - destSz.height())/2);
    videoView->move(center);
}

void FFPlayer::showEvent(QShowEvent *event) {
    printf("FFPlayer showEvent");
    printf("FFPlayer showEvent: %d x %d", size().width(), size().height());
    QSizeF parentSize = parentWidget()->size();
    QSizeF destSz = QSizeF(16, 9).scaled(parentSize, Qt::KeepAspectRatio);
    videoView->resize(QSize(round(destSz.width()), round(destSz.height())));

    QSize psz = size();
    QPoint center((psz.width() - destSz.width())/2, (psz.height() - destSz.height())/2);
    videoView->move(center);
}

void FFPlayer::hideEvent(QHideEvent *event) {
    printf("FFPlayer hideEvent");
}
