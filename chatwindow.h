#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include<udpserver.h>
#include<usrinfo.h>

class UdpServer;
class UsrInfo;
namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    //explicit ChatWindow(QWidget *parent = 0);
    explicit ChatWindow(MainWindow*mainWins,unsigned int myId,unsigned int otherId,UdpServer*udpServer,QWidget *parent = 0);
    explicit ChatWindow(MainWindow*mainWins,UsrInfo*myInfo,UsrInfo*otherInfo,UdpServer*udpServer,QWidget *parent = 0);
    ~ChatWindow();
    void showMsg(const QString&msg);
    //void setIds(unsigned int myId,unsigned int otherId);
private slots:
    void close();

    void on_sendButton_clicked();

private:
    Ui::ChatWindow *ui;
    UsrInfo*myInfo,*otherInfo;
    UdpServer*udpServer;
    MainWindow*mainWins;
};

#endif // CHATWINDOW_H
