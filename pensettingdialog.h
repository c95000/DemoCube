#ifndef PENSETTINGDIALOG_H
#define PENSETTINGDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QButtonGroup>
#include "penstate.h"

class PenSettingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PenSettingDialog(QWidget *parent = nullptr);
    explicit PenSettingDialog(const QColor& color, const int width, QWidget *parent = nullptr);

private:
    void init();

signals:

private:
    QColor penColor;
    int penWidth;

};

#endif // PENSETTINGDIALOG_H
