#include "changeinfo.h"
#include "ui_changeinfo.h"

#include<QLabel>
#include<QLineEdit>
#include<QSqlQuery>
#include<QMessageBox>

ChangeInfo::ChangeInfo(MainWindow*mainWin,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeInfo)
{
    ui->setupUi(this);
    this->mainWin = mainWin;

    info = mainWin->getUsrInfo();

    ui->IdLabel->setText(QString::number(info->getId()));
    ui->nickLineEdit->setText(info->getNick());
    ui->mottoLineEdit->setText(info->getMotto());

}

ChangeInfo::~ChangeInfo()
{
    delete ui;
}

void ChangeInfo::on_characterInfoCancelButton_clicked()
{
    this->hide();
}

void ChangeInfo::on_passwordApplyButton_clicked()
{
    qDebug()<<"on_passwordApplyButton_clicked"<<endl;
    const QString&oldPassword = ui->oldPasswordLineEdit->text();
    const QString&newPassword = ui->newPasswordLineEdit->text();
    const QString&repeatPassword = ui->repeatPasswordLineEdit->text();
    if(oldPassword.isEmpty()||newPassword.isEmpty()||repeatPassword.isEmpty()){
        QMessageBox::warning(this,"警告","密码不能为空!",QMessageBox::Ok);
        return;
    }
    if(newPassword!=repeatPassword){
        QMessageBox::warning(this,"警告","两次输入的密码不相同!",QMessageBox::Ok);
        return;
    }
    QSqlQuery query;
    query.prepare("select * from Account where id=? and password=?;");
    query.addBindValue(info->getId());
    query.addBindValue(oldPassword);
    query.exec();
    if(query.next()){//密码正确
        query.prepare("update Account set password=? where id=?;");
        query.addBindValue(newPassword);
        query.addBindValue(info->getId());
        if(!query.exec()){
            QMessageBox::warning(this,"警告","数据更新失败",QMessageBox::Ok);
            return;
        }
        qDebug()<<"info update success"<<endl;
        this->ui->passwordApplyButton->setEnabled(false);
    }
    else{
        QMessageBox::warning(this,"警告","密码错误!",QMessageBox::Ok);
        return;
    }
}

void ChangeInfo::on_characterApplyButton_clicked()
{
    qDebug()<<"clicked characterApplyButton"<<endl;

    const QString&nick = ui->nickLineEdit->text();
    QString motto = ui->mottoLineEdit->text();
    if(nick.isEmpty()){
        QMessageBox::warning(this,tr("警告"),tr("昵称不能为空!"),QMessageBox::Ok);
        return;
    }
    if(motto.isEmpty()){
        ui->mottoLineEdit->setText(tr("该用户很懒，什么都没有留下~"));
        motto = tr("该用户很懒，什么都没有留下~");
    }
    if(info->getNick()!=nick||info->getMotto()!=motto){
        QSqlQuery query;
        query.prepare("update Account set nick=?,motto=? where id=?;");
        query.addBindValue(nick);
        query.addBindValue(motto);
        query.addBindValue(info->getId());
        bool check = query.exec();
        //bool check = query.exec("update Account set nick='lrc',motto='mychat是宇宙上最好的聊天工具' where id=10000;");
        if(!check){
            QMessageBox::warning(this,tr("警告"),tr("数据更新失败!"),QMessageBox::Ok);
            return;
        }
        qDebug()<<"info update success"<<endl;
        info->updateInfo();
        ui->characterApplyButton->setEnabled(false);
    }
}

void ChangeInfo::on_characterInfoOkButton_clicked()
{
    if(ui->characterApplyButton->isEnabled()){
        on_characterApplyButton_clicked();
    }
    this->hide();
}

void ChangeInfo::on_passwordInfoOkButton_clicked()
{
    if(ui->passwordApplyButton->isEnabled()){
        on_passwordApplyButton_clicked();
    }
    this->hide();
}

void ChangeInfo::on_passwordInfoCancelButton_clicked()
{
    this->hide();
}

void ChangeInfo::setPasswordApplyButtonEnabled(){
    if(ui->oldPasswordLineEdit->text().isEmpty()||
            ui->newPasswordLineEdit->text().isEmpty()||
            ui->repeatPasswordLineEdit->text().isEmpty()){
        return;
    }
    ui->passwordApplyButton->setEnabled(true);
}

void ChangeInfo::setcharacterApplyButtonEnabled(){
    if(ui->nickLineEdit->text().isEmpty()){
        return;
    }
    ui->characterApplyButton->setEnabled(true);
}

void ChangeInfo::on_oldPasswordLineEdit_textChanged(const QString &arg1)
{
    setPasswordApplyButtonEnabled();
}

void ChangeInfo::on_newPasswordLineEdit_textChanged(const QString &arg1)
{
    setPasswordApplyButtonEnabled();
}

void ChangeInfo::on_repeatPasswordLineEdit_textChanged(const QString &arg1)
{
    setPasswordApplyButtonEnabled();
}

void ChangeInfo::on_nickLineEdit_textChanged(const QString &arg1)
{
    setcharacterApplyButtonEnabled();
}

void ChangeInfo::on_mottoLineEdit_textChanged(const QString &arg1)
{
    setcharacterApplyButtonEnabled();
}
