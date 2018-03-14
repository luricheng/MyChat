#include "udpserver.h"

#include<QHostAddress>

UdpServer::UdpServer(unsigned int port, QMap<unsigned int, ChatWindow *> *chatWins,QObject *parent) :
    QObject(parent),
    port(port),
    chatWindows(chatWins)
{
    socket=new QUdpSocket();
    socket->bind(port);
    connect(socket,SIGNAL(readyRead()),this,SLOT(dataReceive()));
}

void UdpServer::showMsgReceive(unsigned int from,const QString&msg){
    auto&chatWins=*chatWindows;
    if(chatWins.find(from)==chatWins.end()){
        chatWins[from]=new ChatWindow(port,from,this);
    }
    ChatWindow*win=chatWins[from];
    win->show();
    win->showMsg(QString::number(from)+":\n"+msg+"\n");
}

void UdpServer::analyzeMessage(const QString&text){
    if(text.isEmpty()){
        return;
    }
    if(text[0]=='*'){//*10001*msg : id=10001发送msg给自身
        QString id;
        int idx=1;
        while(idx<text.length()&&text[idx].isDigit()){
            id+=text[idx];
            ++idx;
        }
        QString msg;
        ++idx;
        while(idx<text.length()){
            msg+=text[idx];
            ++idx;
        }
        unsigned int uIntId;
        bool check;
        uIntId=id.toUInt(&check);
        if(check){
            showMsgReceive(uIntId,msg);
        }
    }
}

void UdpServer::dataReceive(){
    while(socket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(),datagram.size());
        QString msg=QString::fromLocal8Bit(datagram.data());
        qDebug()<<datagram<<"\n"<<msg.toLocal8Bit()<<"\n"<<msg<<endl;
        analyzeMessage(msg);
    }
}

void UdpServer::sendMessage(unsigned int sendPort,const QString &msg){
    if(!msg.isEmpty()){
        socket->writeDatagram(msg.toLocal8Bit(),QHostAddress::Broadcast,sendPort);
    }
}
