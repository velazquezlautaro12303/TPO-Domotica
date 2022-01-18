#include "viewtemperatura.h"
#include <QVBoxLayout>

ViewTemperatura::ViewTemperatura(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    label = new QLabel("Temp: ");

    layout->addWidget(label);
    setLayout(layout);
}

void ViewTemperatura::setTemp(QString cadena)
{
    label->setText(cadena);
}
