#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QWidget>
#include "common.h"
#include <QTcpSocket>
#include <QTextEdit>

class SocketTest : public QWidget
{
    Q_OBJECT
public:
    explicit SocketTest(QWidget *parent = nullptr);
    virtual ~SocketTest();

signals:

private slots:
    void connect();
    void disconnect();
    void sendData();
    void recvData();
    void clearData();

private:
    QPushButton *btnConnect;
    QPushButton *btnDisconnect;
    QPushButton *btnRequest;
    QPushButton *btnSend;
    QPushButton *btnClear;
    QLabel *response;

    QTextEdit *dataSend;
    QTextEdit *dataRecv;

    QTcpSocket* mp_clientSocket;
};

#endif // SOCKETTEST_H
