#include "videorender.h"
#include "common.h"
#include <QResizeEvent>
#include <QtMath>

VideoRender::VideoRender(QWidget *parent) : QWidget(parent)
{
    aspectRatio = 16.0 / 9;
    videoSize = QSizeF(16, 9);
}

VideoRender::VideoRender(const double aspectRatio, QWidget *parent): QWidget(parent), aspectRatio(aspectRatio)
{
    double width = 1.0 * aspectRatio;
    videoSize = QSizeF(width, 1.0);
}

VideoRender::VideoRender(const QSizeF& videoSize, QWidget *parent): QWidget(parent), videoSize(videoSize) {
    aspectRatio = 1.0 * videoSize.width() / videoSize.height();
}

void VideoRender::resizeEvent(QResizeEvent *event) {
    QSizeF parentSize = parentWidget()->size();
    QSizeF destSz = videoSize.scaled(parentSize, Qt::KeepAspectRatio);
    resize(QSize(round(destSz.width()), round(destSz.height())));

    QSize psz = parentWidget()->size();
    QPoint center((psz.width() - size().width())/2, (psz.height() - size().height())/2);
    move(center);
}
