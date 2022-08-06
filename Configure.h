#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QObject>
#include <QSettings>

class Configure: public QObject
{
    Q_OBJECT
private:
    Configure();
    ~Configure();

    static Configure *p;

public:
    static Configure* getInstance()
    {
        if(p == nullptr)
            p = new Configure();
        return p;
    }

public:
    void setValue();

    void getValue();

    QString getPicpath();
    QString getVideopath();
    QString getCameraIp(int index);
    void setCameraIp(int index, const QString& ip);
    bool isAllowCommenting();

    const QSize buttonSize();
    const QColor colorByIndex(int index);
    int widthByIndex(int index);

    QString getUsername() const;
    QString getPassword() const;

    const QList<QColor> getPenColors();
    const QList<int> getPenWidths();

    bool isLicensed() const;
    void setActivateCode(QString code);
private:
//    QString configPath;
    QSettings* configFile;

    QList<QColor> penColors;
    QList<int> penWidth;
    QString license;
    bool bLicensed;
};

#endif // CONFIGURE_H
