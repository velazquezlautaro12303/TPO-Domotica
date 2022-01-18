#include "serialterminal.h"
#include "ui_serialterminal.h"
#include <QMessageBox>
#include <QDebug>
#include <string.h>

static QString addCheckSum(QString cadena);

SerialTerminal::SerialTerminal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialTerminal)
{
    ui->setupUi(this);
    port = NULL;
    portName = "";
    EnumerarPuertos();
    activeSensorPuerta = false;
}

void SerialTerminal::Error()
{
    QMessageBox::critical(this,"Error","Se perdio la conexion, revise su conexion");
    delete port;
    port = NULL;
    EnumerarPuertos();
}

void SerialTerminal::Active_Sensor_Puerta(bool temp)
{
    activeSensorPuerta = temp;
}

void SerialTerminal::SendPersianaAutomatic(bool tmp)
{
    QString data = "R";
    if(tmp)
    {
        data.append("U");
    }
    else
    {
        data.append("D");
    }
    SendDataSerial(data);
}

void SerialTerminal::SubirPersiana()
{
    SendDataSerial("R1");    //REVISAR CODIGO
}

void SerialTerminal::BajarPersiana()
{
    SendDataSerial("R0");    //REVISAR CODIGO
}

SerialTerminal::~SerialTerminal()
{
    delete ui;
    delete port;
}

void SerialTerminal::EnumerarPuertos()
{
    ui->comboBoxPort->clear();

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    if(ports.size() != 0)
    {
        for (int i = 0; i < ports.size(); i++)
        {
            ui->comboBoxPort->addItem(ports.at(i).portName()/*, ports.at(i).portName()*/);
        }
        ui->pushButtonConectar->setText(QString("Conectar"));
    }
    else
    {
        ui->pushButtonConectar->setText(QString("Refresh"));
    }
}

void SerialTerminal::on_pushButtonConectar_clicked()
{
    if(!port && ui->pushButtonConectar->text() == QString("Conectar"))
    {
        port = new QSerialPort(portName);
        port->setBaudRate(QSerialPort::Baud9600);
        port->setFlowControl(QSerialPort::NoFlowControl);
        port->setParity(QSerialPort::NoParity);
        port->setDataBits(QSerialPort::Data8);
        port->setStopBits(QSerialPort::OneStop);
        if(!port->open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this,"Error","No se puede abrir el puerto ");
            delete port;
            port = NULL;
            EnumerarPuertos();
        }
        else
        {
            ui->pushButtonConectar->setText("Desconectar");
            connect(port,SIGNAL(readyRead()),this,SLOT(on_port_readyRead()));
            connect(port, SIGNAL(error(QSerialPort::SerialPortError)), this,SLOT(Error()));
        }
    }
    else
    {
        delete port;
        port = NULL;
        EnumerarPuertos();
    }
}

void SerialTerminal::on_comboBoxPort_currentIndexChanged(int index)
{
    portName = ui->comboBoxPort->itemText(index);
}

void SerialTerminal::SendPercentDimmer(int value)
{
    QString cadena = QString('L');
    if(value < 10 && value >= 0)
    {
        cadena.append('0');
    }
    cadena.append(QString::number(value));
    //cadena = addCheckSum(cadena);
    SendDataSerial(cadena);
}

void SerialTerminal::SendDataSerial(QString cadena)
{
    if(port)
    {
        QByteArray aux;
        aux.append(cadena);
        port->write(aux);
        qDebug() << cadena;
    }
    else
    {
        QMessageBox::critical(this,"Error","No se puede abrir el puerto, Por favor revise su conexion");
    }
}

#define IDLE        0
#define RECIBI_P    1
#define RECIBI_T    2
#define RECIBI_TEMP 3

void SerialTerminal::on_port_readyRead()
{
    if(port)
    {
        static int state = IDLE;
        static int temperatura = 0;
        QByteArray aux;
        aux.resize(port->bytesAvailable());
        port->read(aux.data(),aux.size());
        qDebug() << "Recibo " << aux;

        static int decena = 0;
        static int unidad = 0;

        switch (state) {
            case IDLE:
                if(aux == "P")
                {
                    state = RECIBI_P;
                }
                else if(aux == "T")
                {
                    state = RECIBI_T;
                }
                break;
            case RECIBI_P:
                if(aux == "1")
                {
                     if(activeSensorPuerta)
                     {
                         On_Off_Alarma(1);
                         //qDebug() << "------------------Encender alarma--------------";
                         QMessageBox::StandardButton reply = QMessageBox::critical(this,"Alerta","Se detecto apertura de puerta",QMessageBox::Ok);//Cambiar despues
                         if(reply == QMessageBox::Ok)
                         {
                            //qDebug() << "------------------Apagar alarma--------------";
                            On_Off_Alarma(0);
                         }
                     }
                     state = IDLE;
                }
                else
                {
                    state = IDLE;
                }
                break;
            case RECIBI_T:
                if(aux <= "9" && aux >= "0")
                {
                    decena = aux.toInt();
                    state = RECIBI_TEMP;
                }
                else
                {
                    state = IDLE;
                }
                break;
            case RECIBI_TEMP:
                if(aux <= "9" && aux >= "0")
                {
                    unidad = aux.toInt();
                    if(temperatura != decena*10 + unidad)
                    {
                        temperatura = (decena * 10) + unidad;
                        emit SendTemperature(temperatura);
                        //QMessageBox::critical(this,"Temperatura","Temp: " + QString::number(temperatura) + "º");//Cambiar despues
                    }
                    state = IDLE;
                }
                else
                {
                    state = IDLE;
                }
                break;
        }
    }
}

void SerialTerminal::On_Off_Alarma(int state)
{
    QString cadena = "A";
    cadena.append(QString::number(state));
    cadena = addCheckSum(cadena);

    SendDataSerial(cadena);
}

static QString addCheckSum(QString cadena)
{
    QString tmp = cadena;
    char checksum = cadena.at(0).toLatin1();

    for(int i = 1; i < cadena.length(); i++)
    {
        checksum += cadena.at(i).toLatin1();
    }

    tmp.append(checksum);

    return tmp;
}
