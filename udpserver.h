#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include<QUdpSocket>
#include<chatwindow.h>
#include<QMap>
#include<mainwindow.h>

class MainWindow;
class ChatWindow;
class UdpServer : public QObject
{
    Q_OBJECT
    friend class ChatWindow;
public:
    explicit UdpServer(MainWindow*mainWins,unsigned int port, QMap<unsigned int, ChatWindow *> *chatWins,QObject *parent=0);
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
    MainWindow*mainWins;
};

#endif // UDPSERVER_H
