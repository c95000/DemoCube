#ifndef TITLEBUTTON_H
#define TITLEBUTTON_H

#include <QWidget>
#include <QString>
#include <QPushButton>

namespace Ui {
class TitleButton;
}

class TitleButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)

public:
    explicit TitleButton(QWidget *parent = nullptr);
    ~TitleButton();

    void setText(const QString &text);
    QString text() const;

    void setImages(const QPixmap &pixmaps);

    const QPushButton *pushButton();

private:
    Ui::TitleButton *ui;
};

#endif // TITLEBUTTON_H
