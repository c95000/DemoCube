#ifndef TESTVIEWCONTROLLER_H
#define TESTVIEWCONTROLLER_H

#include <QWidget>

class TestViewController : public QWidget
{
    Q_OBJECT
public:
    explicit TestViewController(QWidget *parent = nullptr);

signals:
    void onFuncButton1Clicked();
};

#endif // TESTVIEWCONTROLLER_H
