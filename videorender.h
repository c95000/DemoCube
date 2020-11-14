#ifndef VIDEORENDER_H
#define VIDEORENDER_H

#include <QObject>
#include <QWidget>

class VideoRender : public QWidget
{
    Q_OBJECT
public:
    explicit VideoRender(QWidget *parent = nullptr);
    explicit VideoRender(const double aspectRatio, QWidget *parent = nullptr);
    explicit VideoRender(const QSizeF& videoSize, QWidget *parent = nullptr);

//protected:
//    virtual void resizeEvent(QResizeEvent *event);

signals:

private:
    double aspectRatio;
    QSizeF videoSize;
};

#endif // VIDEORENDER_H
