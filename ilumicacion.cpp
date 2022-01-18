#include "ilumicacion.h"
#include <QVBoxLayout>

Ilumicacion::Ilumicacion(SerialTerminal &connectionSerial,QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    label_Ilumicaion = new QLabel("ILUMINACION");
    dial = new QDial;
    progressBar = new QProgressBar;

    layout->addWidget(label_Ilumicaion);
    layout->addWidget(dial);
    layout->addWidget(progressBar);
    setLayout(layout);

    connect(dial, SIGNAL(valueChanged(int)), progressBar, SLOT(setValue(int)));
    connect(dial, SIGNAL(valueChanged(int)), &connectionSerial, SLOT(SendPercentDimmer(int)));

    label_Ilumicaion->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    label_Ilumicaion->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    label_Ilumicaion->setStyleSheet("font: 28pt \"MS Shell Dlg 2\"; color: rgb(0, 0, 0);");  //border: none; padding: 0px;

    dial->setMinimumSize(135,135);
    dial->setMaximumSize(1000,135);

    //progressBar->setStyleSheet("text-align:center;");

    layout->layout()->setContentsMargins(50,80,50,80);
}
