#ifndef ASSIST_H
#define ASSIST_H

#include <QObject>
#include <QWidget>
#include "common.h"
#include "iconbutton.h"

class Assist : public QWidget
{
    Q_OBJECT
public:
    explicit Assist(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
signals:

private:
    IconButton *btnSetting;
    IconButton *btnHelp;
};

#endif // ASSIST_H
