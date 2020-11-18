#include "sockettest.h"
#include <QMessageBox>
#include <QInputDialog>

SocketTest::SocketTest(QWidget *parent) : QWidget(parent)
{
    btnConnect = new QPushButton("连接");
    btnDisconnect = new QPushButton("断开");
    btnRequest = new QPushButton("请求");
    btnRequest->hide();
    response = new QLabel("test");
    response->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    btnSend = new QPushButton("发送");
    btnClear = new QPushButton("清除");

    dataSend = new QTextEdit();
    dataRecv = new QTextEdit();


    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(btnConnect);
    hLayout->addWidget(btnDisconnect);
    hLayout->addWidget(btnSend);
    hLayout->addWidget(btnClear);
    hLayout->addStretch();

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(new QLabel("接收区"));
    vLayout->addWidget(dataRecv, 1);
    vLayout->addWidget(new QLabel("发送区"));
    vLayout->addWidget(dataSend, 1);
    vLayout->addLayout(hLayout);

    setLayout(vLayout);

    QObject::connect(btnConnect, SIGNAL(clicked(bool)), this, SLOT(connect()));
    QObject::connect(btnDisconnect, SIGNAL(clicked(bool)), this, SLOT(disconnect()));
    QObject::connect(btnRequest, SIGNAL(clicked(bool)), this, SLOT(sendData()));
    QObject::connect(btnSend, SIGNAL(clicked(bool)), this, SLOT(sendData()));
    QObject::connect(btnClear, SIGNAL(clicked(bool)), this, SLOT(clearData()));

    mp_clientSocket = new QTcpSocket();
}

SocketTest::~SocketTest() {
    delete mp_clientSocket;
}


void SocketTest::connect() {
    printf("%s ", __FUNCTION__);
    QString host = Configure::getInstance()->getCameraIp(1);
    bool isOK;//QInputDialog 是否成功得到输入
    QString text = QInputDialog::getText(NULL,
                                         "设置",
                                         "输入服务器IP:PORT，如: 192.168.1.100:80",
                                         QLineEdit::Normal,
                                         host,
                                         &isOK);
    if(!isOK) {
        return;
    }

    Configure::getInstance()->setCameraIp(1, text);
    printf("text: %s", text.toStdString().c_str());

    QStringList ip_port = text.split(":");

    QString ip = ip_port[0];
    quint16 port = (quint16)ip_port[1].toInt();
    printf("host :%s:%d", ip.toStdString().c_str(), port);
    mp_clientSocket->connectToHost(ip, port);
    if(!mp_clientSocket->waitForConnected(30000))
    {
        QMessageBox::information(this, "SocketTest", "连接服务端失败！");
        return;
    }
    QObject::connect(mp_clientSocket, SIGNAL(readyRead()), this,SLOT(recvData()));
}

void SocketTest::disconnect() {
    printf("%s ", __FUNCTION__);
    mp_clientSocket->close();
}

void SocketTest::sendData() {
    printf("%s ", __FUNCTION__);
    QString message = dataSend->toPlainText();
//    message.append("GET / HTTP/1.1\r\nhost:127.0.0.1\r\nConnection: close\r\n\r\n");
    printf("length:%d \n%s", message.length(), message.toStdString().c_str());

    std::string msg = message.toStdString();
    printf("msg: %d", msg.length());
    int sendRe = mp_clientSocket->write(msg.c_str(), msg.length());
    if(sendRe == -1)
    {
         QMessageBox::information(this, "SocketTest", "向服务端发送数据失败！");
         return;
    }
}

void SocketTest::recvData() {
    printf("%s ", __FUNCTION__);

    char recvMsg[1024] = {0};
    int recvRe = mp_clientSocket->read(recvMsg, 1024);
    printf("%s recvRe:%d", __FUNCTION__, recvRe);
    if(recvRe == -1)
    {
        QMessageBox::information(this, "SocketTest", "接收服务端数据失败！");
        return;
    }
    QString showQstr = recvMsg;
    response->setText(showQstr);
    dataRecv->setText(showQstr);
    dataRecv->toHtml();
}

void SocketTest::clearData() {
    dataRecv->clear();
}
