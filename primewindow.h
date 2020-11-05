#ifndef PRIMEWINDOW_H
#define PRIMEWINDOW_H

#include <QMainWindow>
#include "jyplayer.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedLayout>
#include "mypaint.h"
#include "freedrawing.h"

namespace Ui {
class PrimeWindow;
}

class PrimeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PrimeWindow(QWidget *parent = nullptr);
    ~PrimeWindow();

private slots:
    void on_btnLocal_clicked();
    void on_btnRtsp_clicked();
    void on_btnWhiteboard_clicked();

    void on_btnTest1_clicked();
    void on_btnTest2_clicked();

private:
    Ui::PrimeWindow *ui;

    JyPlayer *m_player = NULL;
    //MyPaint *m_paint = NULL;

};

#endif // PRIMEWINDOW_H
