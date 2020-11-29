#ifndef ACTIVATEDIALOG_H
#define ACTIVATEDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include "common.h"
#include <QLineEdit>

class ActivateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ActivateDialog(QWidget *parent = nullptr);

private:
    void init();

public:
    QString getCode() const;
signals:

private:
    QLineEdit *codeEdit;
};

#endif // ACTIVATEDIALOG_H
