#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include<QUdpSocket>
#include<chatwindow.h>
#include<QMap>

class ChatWindow;
class UdpServer : public QObject
{
    Q_OBJECT
    friend class ChatWindow;
public:
    explicit UdpServer(unsigned int port, QMap<unsigned int, ChatWindow *> *chatWins,QObject *parent=0);
signals:

public slots:
    void dataReceive();

private:
    unsigned int port;
    QUdpSocket*socket;
    QMap<unsigned int,ChatWindow*>*chatWindows;
    void showMsgReceive(unsigned int from,const QString&msg);
    void analyzeMessage(const QString&text);
    void sendMessage(unsigned int sendPort,const QString &msg);
};

#endif // UDPSERVER_H
