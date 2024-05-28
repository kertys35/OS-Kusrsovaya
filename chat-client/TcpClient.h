#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDateTime>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);//наш клиент

signals:
    void newMessage(const QByteArray &ba);//сигнал о новом сообщении
public slots:
    void connectToServer(const QString &ip, const QString &port,const QString &name);//присоединение к серверу
    void sendMessage(const QString &message);//отправка сообщений
    void disconnectFromServer();//отключение от сервера
private slots:
    void onConnected();//в случае подключения
    void onReadyRead();//в случае обмена сообщениями
    void onDisconnected();//в случае отключения
private:
    QTcpSocket Socket;//соккет, через который происходит подключение
    QString Nickname;//имя пользователя
};

#endif // TCPCLIENT_H
