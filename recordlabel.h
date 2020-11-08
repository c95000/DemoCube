#ifndef RECORDLABEL_H
#define RECORDLABEL_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class RecordLabel;
}

class RecordLabel : public QWidget
{
    Q_OBJECT

public:
    explicit RecordLabel(QWidget *parent = nullptr);
    ~RecordLabel();

signals:
    void stopRecord();

    //自定义槽
protected slots:
    void onStopRecord();
    void onTimeUpdate();
    void onShow();

public:
    void startRecord();
    void reset();

    void showEvent(QShowEvent *event) override;

private:
    Ui::RecordLabel *ui;

    QTimer* timer;
    QDateTime startTime;
};

#endif // RECORDLABEL_H