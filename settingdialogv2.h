#ifndef SETTINGDIALOGV2_H
#define SETTINGDIALOGV2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

class SettingDialogV2 : public QDialog
{
    Q_OBJECT
public:
    explicit SettingDialogV2(QWidget *parent = nullptr);
    ~SettingDialogV2();

signals:

protected:
    void resizeEvent(QResizeEvent *event);

protected slots:    //使用slots关键字
    void onChangePicPath();
    void onChangeVideoPath();
    void onSaveIp(int index);

private:
     QDialogButtonBox *buttonBox;
     QLabel *labelPicPath, *labelVideoPath, *labelCh1, *labelCh2, *labelCh3;
     QLineEdit *editPicPath, *editVideoPath, *editCh1, *editCh2, *editCh3;
     QPushButton *btnPicPath, *btnVideoPath, *btnCh1, *btnCh2, *btnCh3;

     QString picPath;
     QString videoPath;

     QString ip1;
     QString ip2;
     QString ip3;
};

#endif // SETTINGDIALOGV2_H
