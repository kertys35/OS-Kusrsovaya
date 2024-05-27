#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDateTime>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);

signals:
    void newMessage(const QByteArray &ba);
public slots:
    void connectToServer(const QString &ip, const QString &port,const QString &name);
    void sendMessage(const QString &message);
private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
private:
    QTcpSocket _socket;
    QString Nickname;
};

#endif // TCPCLIENT_H
