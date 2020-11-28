#include "Configure.h"

#include <QDir>
#include <QSettings>
#include <QStandardPaths>
#include "common.h"
#include <QColor>
#include <QRgba64>

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

QString Configure::getUsername() const {
    QString key = tr("acc/un");
    QString value = configFile->value(key, "admin").toString();
    return QString(value.toUtf8().toBase64());
}

QString Configure::getPassword() const {
    QString key = tr("acc/pw");
    QString value = configFile->value(key, "admin").toString();
    return QString(value.toUtf8().toBase64());
}

const QList<QColor> Configure::getPenColors() {
    if(penColors.isEmpty()) {
        QString key = tr("pen/colors");
        QString value = configFile->value(key, "0xFF0000,0x00FF00,0x0000FF,0xFFFF00").toString();
        QStringList valList = value.split(",");
        for(int i= 0; i < valList.size(); i++) {
    //        result.append(valList.at(i).toInt(NULL, 16));
            QRgb x = valList.at(i).toInt(NULL, 16);
            penColors.append(QColor::fromRgb(x));
        }
    }
    return penColors;
}

const QList<int> Configure::getPenWidths() {
    if(penWidth.isEmpty()) {
        QString key = tr("pen/widths");
        QString value = configFile->value(key, "2,4,6,8").toString();
        QStringList valList = value.split(",");
        for(int i= 0; i < valList.size(); i++) {
            penWidth.append(valList.at(i).toInt());
        }
    }
    return penWidth;
}

const QSize Configure::buttonSize() {
    return QSize(80, 30);
}

const QColor Configure::colorByIndex(int index){
    QColor color = Qt::red;
    if(index < penColors.size()) {
        color = penColors.at(index);
    }
    return color;
}

int Configure::widthByIndex(int index) {
    int width = 2;
    if(index < penWidth.size()) {
        width = penWidth.at(index);
    }
    return width;
}

