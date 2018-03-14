#include "usrinfo.h"
#include "ui_usrinfo.h"

UsrInfo::UsrInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsrInfo)
{
    ui->setupUi(this);
}

void UsrInfo::init(MainWindow*mainWin,unsigned int id, QMap<unsigned int, ChatWindow *> *chatWins, QString motto){
    this->mainWin=mainWin;
    this->id=id;
    this->chatWindows=chatWins;
    this->motto=motto;
    QString idText=QString::number(id);
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
        ChatWindow*p=new ChatWindow(mainWin->getId(),id,mainWin->getUdpServer());
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
