#ifndef ADDSUBBUTTON_H
#define ADDSUBBUTTON_H

#include <QWidget>

namespace Ui {
class AddSubButton;
}

class AddSubButton : public QWidget
{
    Q_OBJECT

public:
    explicit AddSubButton(QWidget *parent = nullptr);
    ~AddSubButton();

private slots:
    void on_btnAdd_clicked();

    void on_btnSub_clicked();

private:
    Ui::AddSubButton *ui;

    int maxValue;
    int currentValue;

};

#endif // ADDSUBBUTTON_H
