/**
 * @file login.h
 * @version 1.0
 * @date 10/09/2021
 */

#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "mainwindow.h"
#include "mysql.h"

namespace Ui {
class Login;
}

/**
 * @brief Esta clase representa el login de la aplicacion
 */
class Login : public QWidget
{
    Q_OBJECT

    public:
        explicit Login(QWidget *parent = nullptr);
        ~Login();

private slots:
    /**
     * @brief Permite el ingreso al menu principal
     */
    void on_pushButton_clicked();

private:
        Ui::Login *ui;
        MainWindow w;
        mysql my_mysql;
};

#endif // LOGIN_H
