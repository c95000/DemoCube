#ifndef THEMEUTILS_H
#define THEMEUTILS_H

#include <QObject>

class ThemeUtils : public QObject
{
    Q_OBJECT
private:
    explicit ThemeUtils(QObject *parent = nullptr);

signals:

public:
    static void setBackground(QWidget* widget, int hexColor, double alpha = 1.0);
};

#endif // THEMEUTILS_H
