#include "TcpClient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    //инициализация сокета
    connect(&Socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(&Socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
}

void TcpClient::connectToServer(const QString &ip, const QString &port,const QString &name)
{
    //присоединение сокета к серверу
    Socket.connectToHost(ip, port.toUInt());
    Nickname=name;
    connect(&Socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
}
void TcpClient::disconnectFromServer()
{
    //удаляет соединение с сервером
    Socket.disconnectFromHost();
}

void TcpClient::sendMessage(const QString &message)
{
    //Отправка сообщения от пользователя
    Socket.write(Nickname.toUtf8()+ ": " + message.toUtf8());
    Socket.flush();
}

void TcpClient::onConnected()
{
    //уведомление о подключении пользователя к чату
    qInfo() << "Пользователь присоединился к серверу.";
    emit newMessage("Вы успешно подключились к чату!");
}

void TcpClient::onReadyRead()
{
    //получение информации от других клиентов чата
    const auto message = Socket.readAll();
    emit newMessage(message);
}
void TcpClient::onDisconnected()
{
    //уведомление об отключении от чата
    const auto client = qobject_cast<QTcpSocket*>(sender());
    if(client==nullptr)
    {
        return;
    }
    emit newMessage("Вы успешно отключились от чата");
}
