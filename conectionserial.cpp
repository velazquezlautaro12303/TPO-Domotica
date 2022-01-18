#include "conectionserial.h"
#include "ui_conectionserial.h"
#include <QMessageBox>

ConectionSerial::ConectionSerial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConectionSerial)
{
    ui->setupUi(this);
    port = NULL;
    portName = "";
    EnumerarPuertos();
}

ConectionSerial::~ConectionSerial()
{
    delete ui;
    delete port;
}

void ConectionSerial::EnumerarPuertos()
{
    ui->comboBoxPort->clear();

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (int i = 0; i < ports.size(); i++)
    {
        ui->comboBoxPort->addItem(ports.at(i).portName()/*, ports.at(i).portName()*/);
    }
}

/*void ConectionSerial::on_pushButtonConectar_clicked()
{
    if(!port)
    {
        port = new QSerialPort(portName);
        port->setBaudRate(QSerialPort::Baud115200);
        port->setFlowControl(QSerialPort::NoFlowControl);
        port->setParity(QSerialPort::NoParity);
        port->setDataBits(QSerialPort::Data8);
        port->setStopBits(QSerialPort::OneStop);
        if(!port->open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this,"Error","No se puede abrir el puerto " + port->portName());
            delete port;
            port = NULL;
        }
        else
        {
            ui->pushButtonConectar->setText("Desconectar");
            connect(port,SIGNAL(readyRead()),this,SLOT(on_port_readyRead()));
        }
    }
    else
    {
        delete port;
        port = NULL;
        ui->pushButtonConectar->setText("Conectar");
    }
}*/

/*void ConectionSerial::on_pushButtonEnviar_clicked()
{
    if(port)
    {
        QByteArray aux;
        aux.append(ui->plainTextEditTX->toPlainText());

        port->write(aux);

        ui->plainTextEditTX->clear();
    }
    else
    {
        QMessageBox::critical(this, "Error", QString::fromUtf8("No hay ningún puerto abierto"));
    }
}*/
