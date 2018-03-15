#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QTextEdit>
#include<QLabel>
#include<QScrollArea>
#include<QSqlQuery>
/*
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
*/

QString getMotto(unsigned int id){//获取签名(座右铭)
    QSqlQuery query;
    query.prepare("select motto from Account where id=?;");
    query.addBindValue(id);
    bool ok = query.exec();
    if(ok&&query.next()){
        return query.value(0).toString();
    }
    qDebug()<<"getMotto error!"<<endl;
    return "";
}

MainWindow::MainWindow(unsigned int id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setStyleSheet("background-image: url(/home/lu/code/QtProject/MyChat/images/mainWinBackGround.jpg)");

    this->id = id;
    udpServer=new UdpServer(id,&chatWindows);//udp

    this->setCentralWidget(ui->widget);

    myInfo = new UsrInfo(this);//设置头像
    myInfo->init(this,id,&chatWindows,getMotto(id));
    friendsBox=new QToolBox();//好友列表

    QVBoxLayout*layout=new QVBoxLayout();//添加进gui中
    layout->addWidget(myInfo);
    layout->addWidget(friendsBox);
    ui->widget->setLayout(layout);

    addFirends(id);//生成好友
    initFriendsList();//导入好友

    chatWindows[id]=nullptr;
}

void MainWindow::initFriendsList(){
    for(QMap<QString,QLinkedList<int>* >::const_iterator it = friends.cbegin();it!=friends.cend();++it){
        const QString&groupName=it.key();
        QWidget*groupWidget=new QWidget();
        friendsBox->addItem(groupWidget,groupName);
        QVBoxLayout*layout=new QVBoxLayout();
        for(int id:*it.value()){
            UsrInfo*usr=new UsrInfo(this);
            usr->init(this,id,&chatWindows,getMotto(id));
            layout->addWidget(usr);
        }
        groupWidget->setLayout(layout);
    }
}

void MainWindow::addFirends(unsigned int id){
    QSqlQuery query;
    query.prepare("select FriId,groupName from Friends where myId=?;");
    query.addBindValue(id);
    query.exec();
    while(query.next()){
        QString groupName = query.value(1).toString();
        bool check;
        int id = query.value(0).toInt(&check);
        if(!check){
            qDebug()<<"error:strId to intId error!"<<endl;
        }
        if(friends.find(groupName)==friends.end()){
            friends[groupName] = new QLinkedList<int>();
        }
        friends[groupName]->append(id);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

unsigned int MainWindow::getId(){
    return id;
}

UdpServer* MainWindow::getUdpServer(){
    return udpServer;
}
