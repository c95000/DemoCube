#include "Configure.h"

#include <QDir>
#include <QSettings>
#include <QStandardPaths>
#include "common.h"

Configure* Configure::p = NULL;

Configure::Configure()
{
    printf("configure: %s", QDir::currentPath().toStdString().c_str());
    configFile = new QSettings(QCoreApplication::applicationDirPath()+"/info.ini", QSettings::IniFormat);

}

Configure::~Configure() {
    delete configFile;
}


void Configure::setValue() {
    configFile->setValue("xxx/x", "1");
}

void Configure::getValue() {
    QString value = configFile->value("xxx/x", "111").toString();
    printf("value:%s", value.toStdString().c_str());
}

QString Configure::getPicpath() {
//    picPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString value = configFile->value(tr("path/picture"),
                                      QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)).toString();
    return value;
}

QString Configure::getVideopath() {
    QString value = configFile->value(tr("path/video"),
                                      QStandardPaths::writableLocation(QStandardPaths::MoviesLocation)).toString();
    return value;
}

QString Configure::getCameraIp(int index) {
    QString key = tr("camera/ip%1").arg(index);
    QString value = configFile->value(key,
                                      tr("192.168.1.100")).toString();
    return value;
}

void Configure::setCameraIp(int index, QString& ip) {
    QString key = tr("camera/ip%1").arg(index);
    configFile->setValue(key, ip);
}

const QSize Configure::buttonSize() {
    return QSize(80, 30);
}
const QColor Configure::colorByIndex(int index){
    QColor color = Qt::red;
    switch (index) {
    case 0:
        color = Qt::red;
        break;
    case 1:
        color = Qt::green;
        break;
    case 2:
        color = Qt::blue;
        break;
    case 3:
        color = Qt::yellow;
        break;
    }
    return color;
}

int Configure::widthByIndex(int index) {
    int width = 2;
    switch (index) {
    case 0:
        width = 2;
        break;
    case 1:
        width = 4;
        break;
    case 2:
        width = 6;
        break;
    case 3:
        width = 8;
        break;
    }
    return width;
}

QString Configure::getUsername() const {
    return QString("YWRtaW4=");
}

QString Configure::getPassword() const {
    return QString("YWRtaW4=");
}
