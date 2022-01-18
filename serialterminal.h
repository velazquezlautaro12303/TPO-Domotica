/**
 * @file serialterminal.h
 * @version 1.0
 * @date 10/09/2021
 */

#ifndef SERIALTERMINAL_H
#define SERIALTERMINAL_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class SerialTerminal;
}

class SerialTerminal : public QWidget
{
    Q_OBJECT

public:
    explicit SerialTerminal(QWidget *parent = nullptr);
    void SendDataSerial(QString cadena);
    ~SerialTerminal();

signals:
    void SendTemperature(int temp);

public slots:
    void on_pushButtonConectar_clicked();
    void on_comboBoxPort_currentIndexChanged(int index);
    void SendPercentDimmer(int value);
    void on_port_readyRead();
    void On_Off_Alarma(int state);
    void Error();
    void Active_Sensor_Puerta(bool temp);
    void SubirPersiana();
    void BajarPersiana();
    void SendPersianaAutomatic(bool tmp);

private:
    Ui::SerialTerminal *ui;
    QString portName;
    QSerialPort *port;
    void EnumerarPuertos();
    bool activeSensorPuerta;
};

#endif // SERIALTERMINAL_H
