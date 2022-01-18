#include "camara.h"
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>

Camara::Camara(QTreeWidgetItem *&_item, SerialTerminal &connectionSerial, timer &_timer, int id_camara,QWidget *parent) : QWidget(parent)
{
    QGridLayout* gridLayout = new QGridLayout;
    mOpenCV_videoCapture = new MyVideoCapture(id_camara,this);
    camara = new QLabel;

    camara->setMaximumSize(457,349);
    gridLayout->addWidget(camara);
    setLayout(gridLayout);
    mOpenCV_videoCapture->start(QThread::HighestPriority);
    item = _item;

    connect(mOpenCV_videoCapture, &MyVideoCapture::newPixmapCaptured, this, &Camara::setPixmap);
    connect(mOpenCV_videoCapture, SIGNAL(SendOnAlarma(int)), &connectionSerial, SLOT(On_Off_Alarma(int)));
    connect(mOpenCV_videoCapture, SIGNAL(ActiveSequence()), this, SLOT(Expand()));
    connect(this, SIGNAL(sendItem(QTreeWidgetItem*&)), &_timer, SLOT(addItem(QTreeWidgetItem*&)));
}

void Camara::setPixmap()
{
    camara->setPixmap(mOpenCV_videoCapture->pixmap().scaled(457,349));
}

void Camara::Expand()
{
    item->parent()->setExpanded(1);
    emit sendItem(item);
}
