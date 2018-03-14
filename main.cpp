#include "mainwindow.h"
#include <QApplication>
#include<login.h>
#include<QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    unsigned int id;
    Login login(&id);
    if(login.exec()==QDialog::Accepted){
        MainWindow w(id);
        w.show();
        return a.exec();
    }
    else{
        return 0;
    }
}
