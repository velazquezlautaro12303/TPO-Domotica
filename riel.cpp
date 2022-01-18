#include "riel.h"
#include <QHBoxLayout>

Riel::Riel(SerialTerminal &connectionSerial, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    arriba = new QRadioButton("Abajo");
    abajo  = new QRadioButton("Arriba");

    layout->addWidget(arriba);
    layout->addWidget(abajo);
    layout->setSpacing(0);
    layout->setMargin(0);

    setLayout(layout);

    connect(arriba, SIGNAL(clicked()),&connectionSerial, SLOT(SubirPersiana()));
    connect(abajo , SIGNAL(clicked()),&connectionSerial, SLOT(BajarPersiana()));
}
