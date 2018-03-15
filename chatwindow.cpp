#include "chatwindow.h"
#include "ui_chatwindow.h"

#include<QDebug>
/*
ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
}
*/

ChatWindow::ChatWindow(MainWindow*mainWins,UsrInfo*myInfo,UsrInfo*otherInfo,UdpServer*udpServer,QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::ChatWindow),
    myInfo(myInfo),
    otherInfo(otherInfo),
    udpServer(udpServer)
{
    ui->setupUi(this);
    this->mainWins=mainWins;
    ui->label->setText(otherInfo->getNick()+'('+QString::number(otherInfo->getId())+')');
}

ChatWindow::ChatWindow(MainWindow*mainWins,unsigned int myId, unsigned int otherId,UdpServer*udpServer, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::ChatWindow),
    udpServer(udpServer)
{
    ui->setupUi(this);
    this->mainWins=mainWins;
    myInfo = mainWins->infoMap[myId];
    otherInfo = mainWins->infoMap[otherId];
    ui->label->setText(otherInfo->getNick()+'('+QString::number(otherInfo->getId())+')');

    //setStyleSheet("background-image: url(/home/lu/code/QtProject/MyChat/images/chatWinBackGround.jpg)");
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::showMsg(const QString &msg){
    ui->textBrowser->insertPlainText(msg);
}

void ChatWindow::close(){
    this->setVisible(false);
}

void ChatWindow::on_sendButton_clicked()
{
    if(ui->textEdit->toPlainText().isEmpty()){
        return;
    }
    QString msg=ui->textEdit->toPlainText();
    ui->textEdit->clear();
    unsigned int myId = myInfo->getId();
    unsigned int otherId = otherInfo->getId();
    ui->textBrowser->insertPlainText(QString::number(myId)+":\n"+msg+"\n");
    msg="*"+QString::number(myId)+"*"+msg+"\n";
    udpServer->sendMessage(otherId,msg);
}
