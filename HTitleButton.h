#ifndef HTITLEBUTTON_H
#define HTITLEBUTTON_H

#include <QWidget>

namespace Ui {
class HTitleButton;
}

class HTitleButton : public QWidget
{
    Q_OBJECT

public:
    explicit HTitleButton(QWidget *parent = nullptr);
    ~HTitleButton();

public:
    void setText(const QString &text);

private:
    Ui::HTitleButton *ui;
};

#endif // HTITLEBUTTON_H
