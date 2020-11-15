#include "progressbar.h"
#include <QHBoxLayout>

ProgressBar::ProgressBar(QWidget *parent) : QWidget(parent)
{
    left = new QLabel("--:--");
    slider = new QSlider();
    slider->setOrientation(Qt::Horizontal);

    right = new QLabel("--:--");

//    QPalette pal(right->palette());
//    pal.setColor(QPalette::Background, QColor(228,228,0)); //设置背景黑色
//    right->setAutoFillBackground(true);
//    right->setPalette(pal);

    QHBoxLayout *hLayout = new QHBoxLayout();

    hLayout->addWidget(left);
    hLayout->addWidget(slider);
    hLayout->addWidget(right);

    setLayout(hLayout);

    connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));

    setMinimumHeight(48);
}

ProgressBar::~ProgressBar() {

}


int ProgressBar::value() const {
    return slider->value();
}

void ProgressBar::reset() {
    slider->triggerAction(QSlider::SliderAction::SliderToMinimum);
}

// msec
void ProgressBar::setValue(int value, int maximum) {
//    printf("value: %d max: %d", value, maximum);
    slider->setValue(value);
    slider->setMaximum(maximum);
    if(QTime::fromMSecsSinceStartOfDay(maximum).hour() > 0) {
        QString max = QTime::fromMSecsSinceStartOfDay(maximum).toString("hh:mm:ss");
        right->setText(max);

        QString curr = QTime::fromMSecsSinceStartOfDay(value).toString("hh:mm:ss");
        left->setText(curr);
    } else {
        QString max = QTime::fromMSecsSinceStartOfDay(maximum).toString("mm:ss");
        right->setText(max);

        QString curr = QTime::fromMSecsSinceStartOfDay(value).toString("mm:ss");
        left->setText(curr);
    }
}

void ProgressBar::resizeEvent(QResizeEvent *event) {
    printf("ProgressBar: %d x %d", event->size().width(), event->size().height());
}
