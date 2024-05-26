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
    explicit TcpServer(QObject *parent=nullptr);
signals:
    void newMessage(const QByteArray &message);
private slots:
    void onNewConnection();
    void onReadyRead();
    void onNewMessage(const QByteArray &byte);
    void onDisconnected();
private:
    QString getClientKey(const QTcpSocket *client);
private:
    QTcpServer _server;
    QHash <QString, QTcpSocket*> _clients;

};

#endif // TCPSERVER_H
