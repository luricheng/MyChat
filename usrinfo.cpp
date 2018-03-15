#include "usrinfo.h"
#include "ui_usrinfo.h"

#include<QDebug>
#include<QSqlQuery>

UsrInfo::UsrInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsrInfo)
{
    ui->setupUi(this);
}

QString UsrInfo::getNick()const{
    return nick;
}

unsigned int UsrInfo::getId()const{
    return id;
}

void UsrInfo::init(MainWindow*mainWin,unsigned int id, QMap<unsigned int, ChatWindow *> *chatWins/*, QString motto*/){
    this->mainWin=mainWin;
    this->id=id;
    this->chatWindows=chatWins;

    //设置motto(签名)
    QSqlQuery query;
    query.prepare("select motto from Account where id=?;");
    query.addBindValue(id);
    bool ok = query.exec();
    if(ok&&query.next()){
        this->motto = query.value(0).toString();
    }
    else{
        qDebug()<<"getMotto error!"<<endl;
    }
    //设置nick(昵称)
    query.prepare("select nick from Account where id=?;");
    query.addBindValue(id);
    ok = query.exec();
    if(ok&&query.next()){
        this->nick = query.value(0).toString();
    }
    else{
        qDebug()<<"getNick error!"<<endl;
    }

    QString idText=nick+'('+QString::number(id)+')';//昵称(id号)
    ui->idLabel->setText(idText);
    ui->mottoLabel->setText(motto);
}

UsrInfo::~UsrInfo()
{
    delete ui;
}

void UsrInfo::on_pushButton_clicked()
{
    auto&chatWins=*chatWindows;
    if(chatWins.find(id)==chatWins.end()){
        ChatWindow*p=new ChatWindow(mainWin,mainWin->infoMap[mainWin->getId()],mainWin->infoMap[id],mainWin->getUdpServer());
        chatWins[id]=p;
    }
    ChatWindow*p=chatWins[id];
    if(p==nullptr){
        return;
    }
    else{
        p->show();
    }
}
