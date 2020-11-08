#include "cameraview.h"
#include "common.h"

CameraView::CameraView(QWidget *parent) : QWidget(parent)
{
    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(128,128,128)); //设置背景黑色
    setAutoFillBackground(true);
    setPalette(pal);
}

CameraView::~CameraView() {

}

void CameraView::onConnect(const QString& sourceUrl) {
    printf("%s() url: %s", __FUNCTION__, sourceUrl.toStdString().c_str());
}

void CameraView::onDisconnect() {
    printf("%s()", __FUNCTION__);
}
