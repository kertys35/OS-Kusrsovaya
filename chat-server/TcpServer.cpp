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
      emit newMessage("Новый пользователь подлючился к чату");
      //добавляем нового клиента в список клиентов и обрабатываем его запросы
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
    emit newMessage("Пользователь отключился от чата");
}

void TcpServer::onReadyRead()
{
    //считываем и выводи информацию с соккета
 const auto client = qobject_cast<QTcpSocket*>(sender());
 if(client==nullptr)
 {
     return;
 }
 const auto message =client->readAll();
 emit newMessage(message);
}

void TcpServer::onNewMessage(const QByteArray &byte)
{
     //записываем информацию нового сообщения
    for(const auto &client : qAsConst(_clients))
    {
        client->write(byte);
        client->flush();
    }
}
