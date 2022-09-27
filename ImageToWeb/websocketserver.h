#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QtWebSockets>
#include <vector>

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketServer();
    ~WebSocketServer();

    void clearClient();

public slots:
    void onNewConnection();

signals:
    qint64 sendBinaryMessage(const QByteArray& message);


private:
    QWebSocketServer* server;
    std::vector<QWebSocket*> clientList;

};

#endif // WEBSOCKETSERVER_H
