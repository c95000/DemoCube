#include <QApplication>
#include <QSize>
#include "ui/homev2_2.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomeV2_2 w;
    QSize size = QSize(16, 9).scaled(QSize(1280, 1280), Qt::KeepAspectRatio);
    w.setFixedSize(size);
    w.show();
    return a.exec();
}
