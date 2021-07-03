#include <QtConcurrent/QtConcurrent>
#include <Configure.h>
#include <QFileDialog>
#include "ArnetWrapper.h"
#include "common.h"
#include <QtConcurrent/QtConcurrent>
#include "Configure.h"

QString Http::m_dest;
Http::Http()
{
}

QByteArray Http::Post(QByteArray data,
                      bool isAsync)
{
    QTimer timer;
    timer.setSingleShot(true);

    QNetworkAccessManager manager;
    QEventLoop eventLoop;

    QObject::connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest request;
    request.setUrl(QUrl(m_dest));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

    timer.start(5000);   // 30 secs. timeout

    QNetworkReply *reply = manager.post(request, data);
    if(!isAsync)
        eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    else
        eventLoop.exec();

    if(timer.isActive()) {
        timer.stop();
        QByteArray response;
        if (reply->error() == QNetworkReply::NoError) {
            response = reply->readAll();
            printf("success. %s", QString(response).toStdString().c_str());
        } else {
            printf("failed");
        }
        reply->deleteLater();
        return response;
    } else {
       // timeout
       QObject::disconnect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
       reply->abort();
    }
    QByteArray response;
    return response;
}

ArnetWrapper::ArnetWrapper()
{
//    ip = "192.168.1.225";
//    username = "YWRtaW4=";
//    password = "YWRtaW4=";
//    //1.设置网络地址
//    Http::setAddr("http://192.168.1.225/");
}

ArnetWrapper::~ArnetWrapper()
{
}


void ArnetWrapper::sendError(int errCode) {
    emit error(errCode);
}

void ArnetWrapper::sendEvent(ArnetEvent event) {
    emit sigEvent(event);
}

bool ArnetWrapper::connect(const QString& ip) {
    this->ip = ip;
    Http::setAddr(tr("http://%1/").arg(ip));
    username = Configure::getInstance()->getUsername();
    password = Configure::getInstance()->getPassword();

    printf("username %s password: %s", username.toUtf8().data(), password.toUtf8().data());

    return login();
}

void ArnetWrapper::disconnect() {
}

void ArnetWrapper::zoomWide() {
    printf("%s is called", __FUNCTION__);
    zoomOps(tr("ZoomWide"));
    QtConcurrent::run(this, &ArnetWrapper::zoomStop);
}

void ArnetWrapper::zoomTele() {
    printf("%s is called", __FUNCTION__);
    zoomOps(tr("ZoomTele"));
    QtConcurrent::run(this, &ArnetWrapper::zoomStop);
}

void ArnetWrapper::zoomStop() {
    printf("%s is called", __FUNCTION__);
    QThread::msleep(250);
    zoomOps(tr("Stop"));
}

void ArnetWrapper::zoomOps(const QString& cmdType) {

    QJsonObject jsonContent;
    jsonContent.insert("PtzCmd", cmdType);
    jsonContent.insert("ParamH", 0);
    jsonContent.insert("ParamV", 0);

    QJsonObject json;
    json.insert("Cmd", tr("ReqPtzCtrl"));
    json.insert("Content", jsonContent);

    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str_content(byte_array);

//    printf("data is: %s", QString(document.toJson(QJsonDocument::Compact)).toStdString().c_str());
//    printf("datalen: %d", QString(document.toJson(QJsonDocument::Compact)).length());

    QString data("ReqUserName=%1&ReqUserPwd=%2&%3");
    data = data.arg(username).arg(password).arg(QString(document.toJson(QJsonDocument::Compact)));
//    printf("new data: %s", data.toStdString().c_str());
//    printf("data lengh: %d", data.toUtf8().length());
//    printf("data sfdas: %s", data.toUtf8().data());
    QByteArray response = Http::Post(data.toUtf8(), false);
    if(!response.isEmpty()) {
//        printf("response: %s", QString(response).toStdString().c_str());
    } else {
        sendError(500);
    }
}

bool ArnetWrapper::login() {
    QJsonObject jsonContent;
    jsonContent.insert("UserName", username);
    jsonContent.insert("Userpwd", password);

    QJsonObject json;
    json.insert("Cmd", tr("ReqHttpLogin"));
    json.insert("Content", jsonContent);

    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str_content(byte_array);


//    printf("data is: %s", byte_array.data());
//    printf("datalen: %d", byte_array.length());

    QByteArray response = Http::Post(byte_array, false);
    if(!response.isEmpty()) {
        printf("response: %s", QString(response).toStdString().c_str());
        return true;
    } else {
        return false;
    }
}

