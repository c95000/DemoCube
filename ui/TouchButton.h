#ifndef TOUCHBUTTON_H
#define TOUCHBUTTON_H

#include <QWidget>
#include <QPushButton>

class TouchButton : public QPushButton
{
    Q_OBJECT
public:
    explicit TouchButton(QWidget *parent = nullptr);
    explicit TouchButton(const QString &text, QWidget *parent = nullptr);
signals:

private:
    void initView();
};

#endif // TOUCHBUTTON_H
