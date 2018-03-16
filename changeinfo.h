#ifndef CHANGEINFO_H
#define CHANGEINFO_H

#include <QWidget>
#include<mainwindow.h>

class MainWindow;
class UsrInfo;
namespace Ui {
class ChangeInfo;
}

class ChangeInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeInfo(MainWindow*mainWin,QWidget *parent = 0);
    ~ChangeInfo();

private slots:
    void on_characterInfoOkButton_clicked();

    void on_characterInfoCancelButton_clicked();

    void on_passwordApplyButton_clicked();

    void on_characterApplyButton_clicked();

    void on_passwordInfoOkButton_clicked();

    void on_passwordInfoCancelButton_clicked();

    void on_oldPasswordLineEdit_textChanged(const QString &arg1);

    void on_newPasswordLineEdit_textChanged(const QString &arg1);

    void on_repeatPasswordLineEdit_textChanged(const QString &arg1);

    void on_nickLineEdit_textChanged(const QString &arg1);

    void on_mottoLineEdit_textChanged(const QString &arg1);

private:
    Ui::ChangeInfo *ui;
    MainWindow*mainWin;
    //
    unsigned int id;
    UsrInfo*info;
    void setPasswordApplyButtonEnabled();
    void setcharacterApplyButtonEnabled();
};

#endif // CHANGEINFO_H
