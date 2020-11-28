#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <QWidget>
#include <QButtonGroup>
#include "iconbutton.h"

namespace Ui {
class Navigator;
}

class Navigator : public QWidget
{
    Q_OBJECT

public:
    explicit Navigator(QWidget *parent = nullptr);
    ~Navigator();

public:
    void setChecked(int index);

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:
    void buttonPressed(int index);
    void buttonReleased(int index);
    void buttonToggled(int index, bool);

private slots:
    void onButtonPressed(int index);
    void onButtonReleased(int index);
    void onButtonToggled(int index, bool);

private:
    Ui::Navigator *ui;
    QButtonGroup *buttonGround;
    QList<QString> items;
};

#endif // NAVIGATOR_H
