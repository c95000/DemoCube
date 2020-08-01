#ifndef HTITLEBUTTON_H
#define HTITLEBUTTON_H

#include <QWidget>
#include <ImageButton.h>

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

    ImageButton *imageButton();

    QPushButton *button();
private:
    Ui::HTitleButton *ui;
};

#endif // HTITLEBUTTON_H
