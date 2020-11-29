#include "common.h"
#include <QStandardPaths>
#include <QDateTime>
#include <QDir>
#include <QCryptographicHash>

//int getDesktopWidth() {
//    int w = QApplication::desktop()->width();
//    if(w <= 0) {
//        return 1920;
//    } else {
//        return w;
//    }
//}

//int getDesktopHeight() {
//    int h = QApplication::desktop()->height();
//    if(h <= 0) {
//        return 1080;
//    } else {
//        return h;
//    }
//}

//float getDensityX() {
//    return getDesktopWidth() / 1920.0f;
//}

void savePixmap(QPixmap &pixmap) {
    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".png";
    if (fileName.length() > 0)
    {
        pixmap.copy().save(fileName);
    }
}

void saveImage(QImage& image) {
//    QString fileName = QDir::currentPath().append(QDateTime::currentDateTime().toString("/yyyy-MM-dd hh-mm-ss-zzz") + ".png");
//    printf("fileName:%s", fileName.toStdString().c_str());
    QString picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString fileName = picPath + QDir::separator() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".png";
    image.save(fileName, "png");
}

QString caculateChecksum(QString src) {
//    QString md5;
//    QByteArray ba,bb;
//    QCryptographicHash md(QCryptographicHash::Md5);
//    ba.append(src);
//    md.addData(src.toUtf8());
//    bb = md.result();
//    md5.append(bb.toHex());
//    return md5;

    QString md5;
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba.append(src);
    md.addData(src.toUtf8());
    bb = md.result();
    md5.append(bb.toHex());
    if(md5.length() > 6) {
        return md5.left(6);
    } else {
        return md5;
    }
}
