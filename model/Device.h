#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QObject *parent = nullptr);
    explicit Device(QString ip, QString name = nullptr, QObject *parent = nullptr);
    // Copy constructor
    explicit Device(const Device& other);

    // Assignment operator
    Device& operator=(const Device& other) {
        if (this != &other) {
            ip = other.ip;
            name = other.name;
        }
        return *this;
    }
    bool operator==(const Device &other) const
    {
        return (ip == other.ip) && (name == other.name);
    }
    bool operator<(const Device& other) const
    {
        return ip < other.ip;
    }
    QString getUrl() const;
signals:

public:
    QString ip;
    QString name;
};


#endif // DEVICE_H
