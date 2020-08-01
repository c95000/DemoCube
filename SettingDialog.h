#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();

protected:
    void resizeEvent(QResizeEvent *event);

protected slots:    //使用slots关键字
    void accept();

    void onChangePicPath();
    void onChangeVideoPath();


private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
