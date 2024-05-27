#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer> //для сервера
#include <QTcpSocket> //для клиентов
#include <QHash>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent=nullptr);//наш сервер
signals:
    void newMessage(const QByteArray &message);//добавление нового сообщения
private slots:
    void onNewConnection();//обработка нового подлюченного клиента
    void onReadyRead();//если сервер готов принимать сообщения
    void onNewMessage(const QByteArray &byte);//обработка нового сообщения
    void onDisconnected();//обработка отключения пользователя
private:
    QString getClientKey(const QTcpSocket *client);//получаем идентификатор клиента
private:
    QTcpServer _server;//наш сервер
    QHash <QString, QTcpSocket*> _clients;//подключенные клиенты
};

#endif // TCPSERVER_H
