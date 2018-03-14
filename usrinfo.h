#ifndef USRINFO_H
#define USRINFO_H

#include <QWidget>
#include<chatwindow.h>
#include<mainwindow.h>

class MainWindow;
namespace Ui {
class UsrInfo;
}

class UsrInfo : public QWidget
{
    Q_OBJECT

public:
    explicit UsrInfo(QWidget *parent = 0);
    ~UsrInfo();
    void init(MainWindow*mainWin,unsigned int id,QMap<unsigned int,ChatWindow*>*chatWins,QString motto=tr("该用户很懒，什么都没有留下~"));

private slots:
    void on_pushButton_clicked();

private:
    Ui::UsrInfo *ui;
    unsigned int id;
    QString motto=tr("该用户很懒，什么都没有留下~");
    QMap<unsigned int,ChatWindow*>*chatWindows;
    MainWindow*mainWin;
};

#endif // USRINFO_H
