#ifndef PLAYPAUSEBUTTON_H
#define PLAYPAUSEBUTTON_H

#include <QPushButton>

class PlayPauseButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PlayPauseButton(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent ( QEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event ) ;
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    virtual  QSize sizeHint () const;
signals:

private:
    QList<QPixmap> pixmapList;
    int m_index;
    bool m_enter;

};

#endif // PLAYPAUSEBUTTON_H
