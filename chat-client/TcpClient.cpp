#include "TcpClient.h"


TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    connect(&_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(&_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
}

void TcpClient::connectToServer(const QString &ip, const QString &port,const QString &name)
{
    _socket.connectToHost(ip, port.toUInt());
    Nickname=name;
}


void TcpClient::sendMessage(const QString &message)
{
    _socket.write(Nickname.toUtf8()+ ": " + message.toUtf8());
    _socket.flush();
}

void TcpClient::onConnected()
{
    qInfo() << "Присоединился к серверу.";
    emit newMessage("Пользователь "+ Nickname.toUtf8() +" подключился к чату");
    emit newMessage(Nickname.toUtf8());
}

void TcpClient::onReadyRead()
{
    const auto message = _socket.readAll();
    emit newMessage(message);
}
void TcpClient::onDisconnected()
{
    const auto client = qobject_cast<QTcpSocket*>(sender());
    if(client==nullptr)
    {
        return;
    }
    emit newMessage("Пользователь " + Nickname.toUtf8() +" отключился от чата");
}
