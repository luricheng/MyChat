#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QTextEdit>
#include<QLabel>
#include<QScrollArea>
#include<QSqlQuery>

#include<QToolBar>
#include<QPushButton>
#include<QStatusBar>
/*
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
*/

void MainWindow::on_changeInfoButton_clicked(){
    qDebug()<<"clicked changeInfoBtn!"<<endl;
    ChangeInfo*changeInfo = new ChangeInfo(this);
    changeInfo->show();
}

MainWindow::MainWindow(unsigned int id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setStyleSheet("background-image: url(/home/lu/code/QtProject/MyChat/images/mainWinBackGround.jpg)");

    this->id = id;
    udpServer=new UdpServer(this,id,&chatWindows);//udp

    this->setCentralWidget(ui->widget);

    myInfo = new UsrInfo(this);//设置头像^
    myInfo->init(this,id,&chatWindows);
    friendsBox=new QToolBox();//好友列表
    infoMap[id]=myInfo;

    QVBoxLayout*layout=new QVBoxLayout();//添加进gui中
    layout->addWidget(myInfo);
    layout->addWidget(friendsBox);
    ui->widget->setLayout(layout);

    addFirends(id);//生成好友
    initFriendsList();//导入好友

    changeInfoButton = new QPushButton(tr("修改信息"));
    ui->statusBar->addWidget(changeInfoButton);

    connect(changeInfoButton,SIGNAL(clicked()),this,SLOT(on_changeInfoButton_clicked()));

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
            usr->init(this,id,&chatWindows);
            layout->addWidget(usr);
            infoMap[id]=usr;
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

UsrInfo*MainWindow::getUsrInfo(){
    return myInfo;
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
