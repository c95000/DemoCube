#ifndef ASPECTRATIOSVGWIDGET_H
#define ASPECTRATIOSVGWIDGET_H

#include <QSvgWidget>
#include <QPainter>
#include <QSvgRenderer>

class AspectRatioSvgWidget : public QSvgWidget {
public:
    AspectRatioSvgWidget(const QString &file, QWidget *parent = nullptr)
        : QSvgWidget(file, parent) {}

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        if (!renderer())
            return;

        // 获取 SVG 的原始 viewBox，即原始尺寸
        QRect viewBox = renderer()->viewBox();

        // 计算维持横宽比的缩放比例
        float scaleX = float(width()) / viewBox.width();
        float scaleY = float(height()) / viewBox.height();
        float scale = qMin(scaleX, scaleY);  // 选择较小的比例因子以维持横宽比

        // 计算绘制区域
        int newWidth = viewBox.width() * scale;
        int newHeight = viewBox.height() * scale;
        int xOffset = (width() - newWidth) / 2;  // 水平居中
        int yOffset = (height() - newHeight) / 2; // 垂直居中

        // 设置 QPainter 的变换
        painter.translate(xOffset, yOffset);
        painter.scale(scale, scale);

        // 使用渲染器渲染 SVG
        renderer()->render(&painter);
    }
};


#endif // ASPECTRATIOSVGWIDGET_H
