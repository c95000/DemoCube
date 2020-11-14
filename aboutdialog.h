#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = nullptr);
    virtual ~AboutDialog();

signals:

private:
    QLabel *software;
    QLabel *company;

    QDialogButtonBox* buttonBox;

};

#endif // ABOUTDIALOG_H
