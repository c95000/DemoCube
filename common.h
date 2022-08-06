#ifndef COMMON_H
#define COMMON_H

#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include "Configure.h"
#include <QResizeEvent>
#include <QDebug>
#include "Resolution.h"

#define printf qDebug

QString caculateChecksum(QString src);

#endif // COMMON_H
