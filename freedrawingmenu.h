#ifndef FREEDRAWINGMENU_H
#define FREEDRAWINGMENU_H

#include <QWidget>
#include <QComboBox>
#include "linestate.h"
#include <QPushButton>

namespace Ui {
class FreeDrawingMenu;
}

class FreeDrawingMenu : public QWidget
{
    Q_OBJECT

public:
    explicit FreeDrawingMenu(QWidget *parent = nullptr);
    ~FreeDrawingMenu();

    QColor& getPenColor();
    int getPenWidth();

signals:
    void penChanged();
    void undo();
    void close();

protected:
    void resizeEvent(QResizeEvent *event);

signals:
    void signalUndo();
    void signalClose();


private slots:
    void on_color_changed(int index);
    void on_width_changed(int index);
    void on_btnUndo();
    void on_btnClose();

private:
    Ui::FreeDrawingMenu *ui;

    QComboBox *colorCombo;
    QComboBox *widthCombo;
    LineState *lineState;
    QPushButton *btnUndo;
    QPushButton *btnClose;

    QColor penColor;
    int penWidth;
//    QList<QColor> colors;
//    QList<int> widths;
//    int colorIndex = 0;
//    int widthIndex = 0;

};

#endif // FREEDRAWINGMENU_H
