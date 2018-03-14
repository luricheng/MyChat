#include "login.h"
#include "ui_login.h"

#include<QMessageBox>
#include<QSqlQuery>
#include<QDebug>

bool connectDb(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("luchat");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("88");
    if(db.open()){
        qDebug()<<"connect database success!"<<endl;
        qDebug()<<QSqlDatabase::drivers()<<endl;
        return true;
    }
    else{
        QMessageBox::warning(0,"警告","无法连接到数据库!",QMessageBox::Ok);
        qDebug()<<"connect database failure!"<<endl;
        return false;
    }
}

Login::Login(unsigned int*id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->id = id;
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    if(ui->idLineEdit->text().isEmpty()||ui->passwordLineEdit->text().isEmpty()){
        QMessageBox::warning(this,tr("请输入账号密码！"),tr("请输入账号密码！"),QMessageBox::Ok);
        return;
    }
    bool check;
    QString idStr = ui->idLineEdit->text();
    *id = idStr.toUInt(&check);
    QString password = ui->passwordLineEdit->text();
    if(check){//监测账号是否为数字
        connectDb();
        QSqlQuery query;
        query.exec(QString("select * from Account where id=")+idStr+" and password="+password+";");
        check = query.next();
        if(check){ //数据库中存在该账号密码 登录成功
            QDialog::accept();
        }
    }
    if(!check){
        QMessageBox::warning(this,tr("账号或密码错误！"),tr("账号或密码错误"),QMessageBox::Ok);
    }
}

void Login::on_cancelButton_clicked()
{
    QDialog::reject();
}

