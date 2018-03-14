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

ChatWindow::ChatWindow(unsigned int myId, unsigned int otherId,UdpServer*udpServer, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::ChatWindow),
    myId(myId),
    otherId(otherId),
    udpServer(udpServer)
{
    ui->setupUi(this);
    ui->label->setText(QString::number(otherId));

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

void ChatWindow::setIds(unsigned int myId, unsigned int otherId)
{
    this->myId=myId;
    this->otherId=otherId;
    //qDebug()<<myId<<" "<<otherId<<endl;
}

void ChatWindow::on_sendButton_clicked()
{
    if(ui->textEdit->toPlainText().isEmpty()){
        return;
    }
    QString msg=ui->textEdit->toPlainText();
    ui->textEdit->clear();
    ui->textBrowser->insertPlainText(QString::number(myId)+":\n"+msg+"\n");
    msg="*"+QString::number(myId)+"*"+msg+"\n";
    udpServer->sendMessage(otherId,msg);
}
