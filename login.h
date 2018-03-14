#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(unsigned int*id,QWidget *parent = 0);
    ~Login();

private slots:
    void on_loginButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::Login *ui;
    unsigned int*id;
};

#endif // LOGIN_H
