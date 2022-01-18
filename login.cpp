#include "login.h"
#include "ui_login.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>

#include <UserType.h>
#include <User.h>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    my_mysql.Connect();
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    User * user= my_mysql.VerifyUsers(ui->lineEdit_Usuario->text(),ui->lineEdit_Password->text());

    if(user != NULL)
    {
        this->close();
        w.LoadUsers(user);
        w.LoadRooms();
        w.LoadListRooms();
        w.LoadLogs();

        w.show();
    }
    else
    {
        QMessageBox::critical(this,"Error","Usuario o Contraseña incorrecta");
        ui->lineEdit_Usuario->clear();
        ui->lineEdit_Password->clear();
    }
}
