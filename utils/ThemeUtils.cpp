#include "ThemeUtils.h"
#include <QWidget>
#include <QPalette>
#include <QColor>

ThemeUtils::ThemeUtils(QObject *parent)
    : QObject{parent}
{

}

void ThemeUtils::setBackground(QWidget* widget, int hexColor, double alpha) {
    int al = alpha * 255;
//    QString style = QString("background-color:#%1%2;").arg(al, 2, 16, QLatin1Char('0')).arg(hexColor, 6, 16, QLatin1Char('0'));
//    qDebug() << style;
//    widget->setStyleSheet("background-color:#ffff00;");
//    widget->setStyleSheet(style);
    QPalette pal = widget->palette();
    QColor color;
    color.setNamedColor(QString("#%1%2").arg(al, 2, 16, QLatin1Char('0')).arg(hexColor, 6, 16, QLatin1Char('0')));
    pal.setColor(QPalette::Background, color);
    widget->setAutoFillBackground(true);
    widget->setPalette(pal);
//    widget->setWindowOpacity(alpha);
}
