#include "websocketserver.h"
#include <QDebug>




WebSocketServer::WebSocketServer()
{

    //���죺QWebSocketServer��const QString& serverName,QWebSocketServer::SslMode secureMode,QObject *parent=nullptr��
    //ʹ�ø�����serverName����һ���µ�QWebSocketServer��
    //�÷��������ƽ���HTTP���ֽ׶α�����ʶ���������������Ϊ�գ���ʱ���Ὣ���������Ʒ��͸��ͻ��ˡ�
    //SslModeָʾ��������ͨ��wss��SecureMode������ws��NonSecureMode������
    //QWebSocketServer::SecureMode�������԰�ȫģʽ���У�ͨ��wss��
    //QWebSocketServer::NonSecureMode�������Էǰ�ȫģʽ���У�ͨ��ws��
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

    //�յ���Ϣ
    connect(socket, &QWebSocket::textMessageReceived, [this](const QString& msg) {
        qDebug() << (msg);
    });

    //������Ϣ
    connect(this, &WebSocketServer::sendBinaryMessage, socket, &QWebSocket::sendBinaryMessage);

    //�Ͽ����ӣ��ͷ�
    connect(socket, &QWebSocket::disconnected, [this, socket]() {
        clientList.clear();
        socket->deleteLater();
    });
}

