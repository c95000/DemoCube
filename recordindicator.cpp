#include "recordindicator.h"
#include "common.h"
#include <QPainter>
#include <QResizeEvent>

RecordIndicator::RecordIndicator(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeUpdate()));
//    start();
}


// Event handlers
void RecordIndicator::paintEvent(QPaintEvent *event) {
    if(!isRecording) {
        return;
    }
    QPainter painter(this);

//    painter.setPen(QColor(160, 160, 160));
//    // 上面画线
//    painter.drawLine(0, 0, this->width() - 1, 0);
//    // 左面画线
//    painter.drawLine(0, 0, 0, this->height() - 1);
//    // 右侧画线
//    painter.drawLine(width() - 1, 0, width() - 1, this->height() - 1);
//    // 下面画线
//    painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);


    QFont font;
    font.setPixelSize(12);
    painter.setFont(font);


    qint64 timeDuration = QDateTime::currentMSecsSinceEpoch() - startTimeMs;
    QString text = tr("录制中 %1").arg(QTime::fromMSecsSinceStartOfDay(timeDuration).toString("hh:mm:ss"));

//    QFontMetricsF fontMetrics(font);
//    qreal textWidth = fontMetrics.width(text);
//    qreal textHeight = fontMetrics.height();
//    setMinimumWidth(textWidth + 20, textHeight);
//    setMinimumSize(QSize(textWidth, textHeight));

    painter.setPen(QPen(QColor(20, 20, 20), 2));
    QTextOption option(Qt::AlignBaseline);
    option.setWrapMode(QTextOption::WordWrap);
    QRectF rect(0, 0, this->width(), this->height());
    painter.drawText(18, 0, this->width(), this->height(), Qt::AlignVCenter, text);



    if(isShowRedball) {
        // draw red ball
        painter.translate(8, height()/2);
        painter.setPen(QPen(Qt::gray, 2));//设置画笔bai形式du
        painter.setBrush(QColor(255, 0, 0));//设置画刷zhi，如果不画实dao现的直接内把Brush设置为容setBrush(Qt::NoBrush);
        painter.drawEllipse(QPoint(0, 0), 4, 4);
    }
    isShowRedball = !isShowRedball;


    // end of painting
    painter.end();
}

void RecordIndicator::resizeEvent(QResizeEvent *event) {

}

void RecordIndicator::start() {
    startTimeMs = QDateTime::currentMSecsSinceEpoch();
    timer->start(500);
    isRecording = true;
}

void RecordIndicator::stop() {
    isRecording = false;
    timer->stop();
    startTimeMs = QDateTime::currentMSecsSinceEpoch();
    update();
}

void RecordIndicator::onTimeUpdate() {
    printf("%s" ,tr("onTimeUpdate : %1").arg(QDateTime::currentDateTime().toString()).toStdString().c_str());
    update();
}

//// Event handlers
//bool RecordIndicator::event(QEvent *event) {
//    printf("RecordIndicator event: %d", event->type());
//    return false;
//}
