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

bool Configure::isAllowCommenting() {
    QString key = tr("block/ac");
    bool value = configFile->value(key, false).toBool();
    return value;
}

bool Configure::isOfficial() {
    QString key = tr("block/offi");
    bool value = configFile->value(key, false).toBool();
    return value;
}
