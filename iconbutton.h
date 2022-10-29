#ifndef ICONBUTON_H
#define ICONBUTON_H

#include <QObject>
#include <QWidget>
#include "common.h"
#include <QPushButton>
#include <QToolButton>

class IconButton : public QToolButton
{
    Q_OBJECT
public:
    explicit IconButton(QWidget *parent = nullptr);
    explicit IconButton(const QString& title, QWidget *parent = nullptr);
    explicit IconButton(const QString& icon, const QString& activeIcon, QWidget *parent = nullptr);
    explicit IconButton(const QString& title, const QString& icon, const QString& activeIcon, QWidget *parent = nullptr);

    void setIcon(const QIcon &icon);
private:
    void init();

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *) override;
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    // Event handlers
    bool event(QEvent *event) override;
signals:

private:
    QIcon defaultIcon;
    QIcon activateIcon;
    QString title;
    bool m_bTouchEnd = false;
};

#endif // ICONBUTON_H
