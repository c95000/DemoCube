#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QPushButton>

class ImageButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ImageButton(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent ( QEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event ) ;
    virtual void mouseReleaseEvent ( QMouseEvent * event );
//    virtual QSize sizeHint () const;
//    virtual void resizeEvent(QResizeEvent *event);

public:
    void setImages(const QPixmap &pixmaps);

private:
    QList<QPixmap> pixmapList;
    int m_index;
    bool m_enter;

};

#endif // IMAGEBUTTON_H
