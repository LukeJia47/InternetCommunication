#include "websocketserver.h"
#include <QDebug>




WebSocketServer::WebSocketServer()
{

    //构造：QWebSocketServer（const QString& serverName,QWebSocketServer::SslMode secureMode,QObject *parent=nullptr）
    //使用给定的serverName构造一个新的QWebSocketServer。
    //该服务器名称将在HTTP握手阶段被用来识别服务器。它可以为空，此时不会将服务器名称发送给客户端。
    //SslMode指示服务器是通过wss（SecureMode）还是ws（NonSecureMode）运行
    //QWebSocketServer::SecureMode服务器以安全模式运行（通过wss）
    //QWebSocketServer::NonSecureMode服务器以非安全模式运行（通过ws）
    server = new QWebSocketServer("Server", QWebSocketServer::NonSecureMode, this);

    if (this->server->listen(QHostAddress::Any, 45566))
    {
        QObject::connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    }
    else
    {
        qDebug() << "InspectionServer: failed to listen";
    }

}

WebSocketServer::~WebSocketServer()
{
    clearClient();
    server->close();
}

void WebSocketServer::clearClient()
{
    for (int i = clientList.size() - 1; i >= 0; i--)
    {
        //qDebug()<<i;
        clientList.at(i)->disconnect();
        clientList.at(i)->close();
    }
    qDeleteAll(clientList);
    clientList.clear();
}

void WebSocketServer::onNewConnection()
{
    QWebSocket* socket = server->nextPendingConnection();
    if (!socket)
        return;
    clientList.push_back(socket);
    qDebug() << (QString("[New Connect] Address:%1  Port:%2")
        .arg(socket->peerAddress().toString())
        .arg(socket->peerPort()));

    //收到消息
    connect(socket, &QWebSocket::textMessageReceived, [this](const QString& msg) {
        qDebug() << (msg);
    });

    //发送消息
    connect(this, &WebSocketServer::sendBinaryMessage, socket, &QWebSocket::sendBinaryMessage);

    //断开连接，释放
    connect(socket, &QWebSocket::disconnected, [this, socket]() {
        clientList.clear();
        socket->deleteLater();
    });
}

