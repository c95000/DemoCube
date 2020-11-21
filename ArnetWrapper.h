#ifndef ARNETWRAPPER_H
#define ARNETWRAPPER_H

#include <QObject>
#include "common.h"
#include <QMap>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include "qdebug.h"
#include <QFileInfo>

class Http
{
public:
    enum ErrorType
    {
        NoError = 0,
        ResponseError,
        NetworkError
    };

    Http();

    static void setAddr(QString addr)
    { m_dest = addr; }
    static QByteArray Post(QByteArray,
                           bool isAsync = true);
//    static QByteArray Get(QByteArray,
//                          bool isAsync = true);

private:
    static QString m_addr;
    static QString m_dest;
};

struct PtzZoomCtrl {
    QString PtzCmd;  //ZoomWide  ZoomTele
    int ParamH;
    int ParamV;
};

struct PtzCtrl {
    QString Cmd;
    union {
        PtzZoomCtrl zoomCtrl;
    } Content;
};

class ArnetWrapper:public QObject
{
    Q_OBJECT
public:
    ArnetWrapper();
    virtual ~ArnetWrapper();

private:
    void zoomStop();
    void zoomOps(const QString& ops);
    void login();
    QString version();
    QString& url() const;


    void sendError(int errCode);

signals:
    void error(int);

public slots:
    void connect(const QString&);
    void disconnect();
    void zoomWide(); //  缩小
    void zoomTele(); //  放大

public:
    QString ip;
    QString username;
    QString password;

};

#endif // ARNETWRAPPER_H
