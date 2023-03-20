#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QWidget>
#include <QDialog>
#include "ui/TouchButton.h"
#include "model/DeviceModel.h"

class MenuDialog : public QWidget
{
    Q_OBJECT
public:
    explicit MenuDialog(QWidget *parent = nullptr);
    ~MenuDialog();
signals:
    void onButtonClicked(QString ip);
    void onModelClicked(Device& device);

private:
    void initView();
    void resizeEvent(QResizeEvent *) override;

private:
    QList<TouchButton*> buttons;
    QList<DeviceModel*> dataList;
    DeviceModel deviceModel;
};

#endif // MENUDIALOG_H
