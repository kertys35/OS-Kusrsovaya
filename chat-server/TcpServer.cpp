#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    //инициализация сервера
    connect(&Server, &QTcpServer::newConnection,this,&TcpServer::onNewConnection);
      connect(this, &TcpServer::newMessage, this, &TcpServer::onNewMessage);
       if(Server.listen(QHostAddress::Any, 30000))
           qInfo()<<"Доступен порт";
}
void TcpServer::onNewConnection()
{
    //заносится новый соккет в список соккетов клиентов
    const auto client=Server.nextPendingConnection();
    if(client==nullptr)
    {
        return;
    }
      qInfo() <<"Подключился новый пользователь";
      emit newMessage("Новый пользователь подлючился к чату");
      //добавляем нового клиента в список клиентов и обрабатываем его запросы
       Clients.insert(this->getClientKey(client),client);
       connect(client, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
       connect(client, &QTcpSocket::disconnected, this, &TcpServer::onDisconnected);
}

QString TcpServer::getClientKey(const QTcpSocket *client)
{
    //возвращает адрес и порт подключения клиента
    return client->peerAddress().toString().append(": ").append(QString::number(client->peerPort()));
}

void TcpServer::onDisconnected()
{
    //в случае отключения пользователя выводим сообщение и исключаем соккет из списка клиентов
    const auto client = qobject_cast<QTcpSocket*>(sender());
    if(client==nullptr)
    {
        return;
    }
    Clients.remove(this->getClientKey(client));
    emit newMessage("Пользователь отключился от чата");
}

void TcpServer::onReadyRead()
{
    //считываем и выводим информацию с соккета
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
     //записываем информацию нового сообщения на все соккеты подлюченных клиентов
    for(const auto &client : qAsConst(Clients))
    {
        client->write(byte);
        client->flush();
    }
}
