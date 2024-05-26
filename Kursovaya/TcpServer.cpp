#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    connect(&_server, &QTcpServer::newConnection,this,&TcpServer::onNewConnection);
      connect(this, &TcpServer::newMessage, this, &TcpServer::onNewMessage);
       if(_server.listen(QHostAddress::Any, 30000))
           qInfo()<<"Доступен порт";
}
void TcpServer::onNewConnection()
{
    const auto client=_server.nextPendingConnection();
    if(client==nullptr)
    {
        return;
    }
      qInfo() <<"Подключился новый пользователь";
       _clients.insert(this->getClientKey(client),client);
       connect(client, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
       connect(client, &QTcpSocket::disconnected, this, &TcpServer::onDisconnected);
}

QString TcpServer::getClientKey(const QTcpSocket *client)
{
    return client->peerAddress().toString().append(": ").append(QString::number(client->peerPort()));
}

void TcpServer::onDisconnected()
{
    const auto client = qobject_cast<QTcpSocket*>(sender());
    if(client==nullptr)
    {
        return;
    }
    _clients.remove(this->getClientKey(client));
}

void TcpServer::onReadyRead()
{
 const auto client = qobject_cast<QTcpSocket*>(sender());
 if(client==nullptr)
 {
     return;
 }
 const auto message =this->getClientKey(client).toUtf8() + ": " + client->readAll();
 emit newMessage(message);
}

void TcpServer::onNewMessage(const QByteArray &byte)
{
    for(const auto &client : qAsConst(_clients))
    {
        client->write(byte);
        client->flush();
    }
}
