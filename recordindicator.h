#ifndef RECORDINDICATOR_H
#define RECORDINDICATOR_H

#include <QObject>
#include <QWidget>
#include <QDateTime>
#include <QTimer>

class RecordIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit RecordIndicator(QWidget *parent = nullptr);


public slots:
    void start();
    void stop();

private slots:
    void onTimeUpdate();

signals:

protected:
    // Event handlers
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
//    // Event handlers
//    bool event(QEvent *event) override;

private:
    QTimer* timer;
    qint64 startTimeMs;
    bool isShowRedball = false;
    bool isRecording = false;
};

#endif // RECORDINDICATOR_H
