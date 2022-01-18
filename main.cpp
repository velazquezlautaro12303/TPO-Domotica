#include <QMainWindow>
#include "login.h"
#include <QApplication>
#include <QStyleFactory>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    Login l;
    l.show();
    return a.exec();
}

