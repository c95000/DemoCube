#ifndef SCALER_H
#define SCALER_H

#include <QObject>
#include <QApplication>

class Scaler : public QObject
{
    Q_OBJECT
public:
    explicit Scaler(QApplication *app);

signals:


public:
    double scaleX();
    double scaleY();

private:
    QDesktopWidget *desktopWidget;
    double sx;
    double sy;
};

#endif // SCALER_H
